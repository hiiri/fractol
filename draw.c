/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:34:51 by alcohen           #+#    #+#             */
/*   Updated: 2020/07/31 18:56:13 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

long double			scale(int in_range[2], long double out_range[2])
{
	long double	slope;

	slope = 1.0 * (out_range[1] - out_range[0]) / (in_range[1] - in_range[0]);
	return (slope);
}

static void			pixel_to_image(t_image *image, int x, int y, int color)
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
}

long double			tmpscale(int n, long double old[2], long double new[2])
{
	long double result;

	result = (new[1] - new[0]) * (n - old[0]) / (old[1] - old[0]) + new[0];
	return (result);
}

void				julia(t_thread *td, t_mlx *mlx, int px, int py)
{
	int			iter;
	int			xy_loop[2];
	long double	x;
	long double	y;
	int			color;
	double		xtemp;
	long double	new_re;
	long double	new_im;
	long double	creal;
	long double	cimag;
	long double	slope[2];
	long double	xy_scaled[2];
	long double	old_re;
	long double	old_im;

	xy_loop[0] = WINDOW_WIDTH / MAX_THREADS * td->num;
	xy_loop[1] = 0;
	creal = -0.8 + 0.6 * sin(mlx->mouse_x / (3.14 * 100));
	cimag = 0.156 + 0.4 * cos(mlx->mouse_y / (3.14 * 20));
	slope[0] = scale((int[2]){0, WINDOW_WIDTH}, \
					(long double[2]){mlx->re1, mlx->re2});
	slope[1] = scale((int[2]){0, WINDOW_HEIGHT}, \
					(long double[2]){mlx->im1, mlx->im2});
	while (xy_loop[0] < px)
	{
		xy_loop[1] = 0;
		while (xy_loop[1] < py)
		{
			x = 0.0;
			y = 0.0;

			new_re = 1.5 * (xy_loop[0] - WINDOW_WIDTH / 2) / (0.5 * mlx->zoom * WINDOW_WIDTH) + (mlx->offset[0] * 0.001);
			new_im = (xy_loop[1] - WINDOW_HEIGHT / 2) / (0.5 * mlx->zoom * WINDOW_HEIGHT) + (mlx->offset[1] * 0.001);
			//new_re = tmpscale(xy_loop[0], (long double[2]){0, WINDOW_WIDTH},
		//(long double[2]){-2.0, 1.0});
			//new_im = tmpscale(xy_loop[1], (long double[2]){0, WINDOW_HEIGHT},
		//(long double[2]){-1.0, 1.0});
			iter = 0;
			while (new_re * new_re + new_im * new_im < 4 && iter < mlx->max_iter)
			{
				old_re = new_re;
				old_im = new_im;
				new_re = old_re * old_re - old_im * old_im + creal;
				new_im = 2 * old_re * old_im + cimag;
				// xtemp = new_re * new_re - new_im * new_im + creal + xy_scaled[0];
				// new_im = 2 * new_re * new_im + cimag + xy_scaled[1];
				// new_re = xtemp;
				iter++;
			}
			if (iter == mlx->max_iter)
				color = 0;
			else
				color = iter * 0x0000C8;
			pixel_to_image(mlx->image, xy_loop[0], xy_loop[1], color);
			xy_loop[1]++;
		}
		xy_loop[0]++;
	}
}

void				mandelbrot(t_thread *td, t_mlx *mlx, int px, int py)
{
	long double	xy_scaled[2];
	int			iter;
	int			xy_loop[2];
	long double	x;
	long double	y;
	long double	slope[2];
	int			color;
	long		double x2;
	long double	y2;
	long double	w;

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
			x = 0.0;
			y = 0.0;
			xy_scaled[0] = slope[0] * (xy_loop[0] + mlx->offset[0]) * mlx->zoom;
			xy_scaled[1] = slope[1] * (xy_loop[1] + mlx->offset[1]) * mlx->zoom;
			x2 = 0.0;
			y2 = 0.0;
			w = 0.0;
			iter = 0;
			while (x2 + y2 <= 4 && iter < mlx->max_iter)
			{
				x = (x2 - y2 + xy_scaled[0]);
				y = (w - x2 - y2 + xy_scaled[1]);
				x2 = x * x;
				y2 = y * y;
				w = (x + y) * (x + y);
				iter++;
			}
			if (iter == mlx->max_iter)
				color = 0;
			else
				color = 0xFFFFF0 * iter;
			pixel_to_image(mlx->image, xy_loop[0], xy_loop[1], color);
			xy_loop[1]++;
		}
		xy_loop[0]++;
	}
}

void				burning_ship(t_thread *td, t_mlx *mlx, int px, int py)
{
	long double	xy_scaled[2];
	int			iter;
	int			xy_loop[2];
	long double	x;
	long double	y;
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
			x = 0.0;
			y = 0.0;
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
			if (iter == mlx->max_iter)
				color = 0;
			else
				color = 0xFDFFF8 * (iter / 2);
			pixel_to_image(mlx->image, xy_loop[0], xy_loop[1], color);
			xy_loop[1]++;
		}
		xy_loop[0]++;
	}
}
