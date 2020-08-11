/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:34:51 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/11 17:20:54 by alcohen          ###   ########.fr       */
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
