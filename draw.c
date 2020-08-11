/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:34:51 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/11 16:35:41 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

long double			scale(int in_range[2], long double out_range[2])
{
	long double	slope;

	slope = 1.0 * (out_range[1] - out_range[0]) / (in_range[1] - in_range[0]);
	return (slope);
}

void				px_to_img(t_image *image, int x, int y, int color)
{
	image->image[x * 4 + y * image->size_line] = color % 256;
	image->image[x * 4 + y * image->size_line + 1] = color / 256 % 256;
	image->image[x * 4 + y * image->size_line + 2] = color / 256 / 256 % 256;
}

static void			*draw_fractal_part(void *data)
{
	t_thread		*td;
	t_mlx			*mlx;
	unsigned int	part_width;

	td = data;
	mlx = td->mlx;
	part_width = WINDOW_WIDTH / MAX_THREADS * (td->num + 1);
	if (mlx->fractal == MANDELBROT)
		mandelbrot(td, mlx, part_width, WINDOW_HEIGHT);
	else if (mlx->fractal == JULIA)
		julia(td, td->mlx, part_width, WINDOW_HEIGHT);
	else if (mlx->fractal == BURNING_SHIP)
		burning_ship(td, mlx, part_width, WINDOW_HEIGHT);
	return (NULL);
}

void				handle_drawing(t_mlx *mlx)
{
	pthread_t	thread_id[MAX_THREADS];
	t_thread	threads[MAX_THREADS];
	int			i;
	int			ret;

	i = 0;
	while (i < MAX_THREADS)
	{
		threads[i].size = WINDOW_WIDTH / MAX_THREADS;
		threads[i].num = i;
		threads[i].mlx = mlx;
		ret = pthread_create(&thread_id[i], NULL, \
							draw_fractal_part, &threads[i]);
		if (ret != 0)
			handle_error(ERROR_CREATING_THREAD);
		i++;
	}
	i = 0;
	while (i < MAX_THREADS)
	{
		pthread_join(thread_id[i], NULL);
		i++;
	}
	mlx_put_image_to_window(mlx->init, mlx->window, mlx->image->img_ptr, 0, 0);
	draw_gui(mlx);
}

void				burning_ship(t_thread *td, t_mlx *mlx, int px, int py)
{
	long double	xy_scaled[2];
	int			iter;
	int			xy_loop[2];
	long double	slope[2];
	int			color;
	double		xtemp;
	long double zy;
	long double zx;

	mlx->re1 = -2.0 * mlx->zoom;
	mlx->re2 = 1.0 * mlx->zoom;
	mlx->im1 = -1.0 * mlx->zoom;
	mlx->im2 = 1.0 * mlx->zoom;
	xy_loop[0] = WINDOW_WIDTH / MAX_THREADS * td->num;
	xy_loop[1] = 0;
	slope[0] = scale((int[2]){0, WINDOW_WIDTH}, \
					(long double[2]){mlx->re1, mlx->re2});
	slope[1] = scale((int[2]){0, WINDOW_HEIGHT}, \
					(long double[2]){mlx->im1, mlx->im2});
	while (xy_loop[0] < px)
	{
		xy_loop[1] = 0;
		while (xy_loop[1] < py)
		{
			xy_scaled[0] = slope[0] * (xy_loop[0] + mlx->offset[0]);
			xy_scaled[1] = slope[1] * (xy_loop[1] + mlx->offset[1]);
			iter = 0;
			zx = 0.0;
			zy = 0.0;
			while (zx * zx + zy * zy < 4 && iter < mlx->max_iter)
			{
				xtemp = zx * zx - zy * zy + xy_scaled[0];
				zy = fabsl(2 * zx * zy + xy_scaled[1]);
				zx = fabsl(xtemp);
				iter++;
			}
			color = palette(mlx, iter, (int[3]){zx, zy, xy_loop[0]});
			px_to_img(mlx->image, xy_loop[0], xy_loop[1], color);
			xy_loop[1]++;
		}
		xy_loop[0]++;
	}
}
