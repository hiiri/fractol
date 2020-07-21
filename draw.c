/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:34:51 by alcohen           #+#    #+#             */
/*   Updated: 2020/07/21 18:12:46 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fractol.h"

long double		scale(int in_range[2], long double out_range[2])
{
	long double	slope;

	slope = 1.0 * (out_range[1] - out_range[0]) / (in_range[1] - in_range[0]);
	return (slope);
}

static void		pixel_to_image(t_image *image, int x, int y, int color)
{
	image->image[x * 4 + y * image->size_line] = color;
	image->image[x * 4 + y * image->size_line + 1] = color;
	image->image[x * 4 + y * image->size_line + 2] = color;
}

void			handle_drawing(t_mlx *mlx)
{
	if (mlx->fractal == MANDELBROT)
		mandelbrot(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	else if (mlx->fractal == JULIA)
		julia(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_put_image_to_window(mlx->init, mlx->window, mlx->image->img_ptr, 0, 0);
}

long double 	tmpscale(int n, long double old[2], long double new[2])
{
	long double result;

	result = (new[1] - new[0]) * (n - old[0]) / (old[1] - old[0]) + new[0];
	return (result);
}

void			julia(t_mlx *mlx, int px, int py)
{
	int			iter;
	int			xy_loop[2];
	long double	x;
	long double	y;
	int 		color;
	double 		xtemp;
	long double cx;
	long double cy;
	long double creal;
	long double cimag;

	xy_loop[0] = 0;
	xy_loop[1] = 0;

	creal=-0.8+0.6*sin(mlx->mouse_x/(3.14*100));
    cimag=0.156+0.4*cos(mlx->mouse_y/(3.14*20));
	while (xy_loop[0] < px)
	{
		xy_loop[1] = 0;
		while (xy_loop[1] < py)
		{
			x = 0.0;
			y = 0.0;
			cx = tmpscale(xy_loop[0], (long double[2]){0, WINDOW_WIDTH},
		(long double[2]){-2.0, 1.0});
			cy = tmpscale(xy_loop[1], (long double[2]){0, WINDOW_HEIGHT},
		(long double[2]){-1.0, 1.0});
			iter = 0;
			while (cx * cx + cy * cy < 4 && iter < mlx->iter)
			{
				xtemp = cx * cx - cy * cy + creal;
				cy = 2 * cx * cy + cimag;
				cx = xtemp;
				iter++;
			}
			if (iter == mlx->iter)
				color = 0;
			else
				color = iter * 0x0000C8;
			pixel_to_image(mlx->image, xy_loop[0], xy_loop[1], color);
			xy_loop[1]++;
		}
		xy_loop[0]++;
	}

}

void			mandelbrot(t_mlx *mlx, int px, int py)
{
	long double	xy_scaled[2];
	int		iter;
	int		xy_loop[2];
	long double	x;
	long double	y;
	long double	slope[2];
	int color;

	mlx->re1 = -2.0 * mlx->zoom;
	mlx->re2 = 1.0 * mlx->zoom;
	mlx->im1 = -1.0*mlx->zoom;
	mlx->im2 = 1.0*mlx->zoom;
	xy_loop[0] = 0;
	xy_loop[1] = 0;
	double xtemp;
	slope[0] = scale((int[2]){0, WINDOW_WIDTH}, (long double[2]){mlx->re1, mlx->re2});
	slope[1] = scale((int[2]){0, WINDOW_HEIGHT}, (long double[2]){mlx->im1, mlx->im2});
	long double zy;
	long double zx;
	while (xy_loop[0] < px)
	{
		xy_loop[1] = 0;
		// y loop
		while (xy_loop[1] < py)
		{
			x = 0.0;
			y = 0.0;
			// x loop
			// mouse move offset goes in (xy_loop[] + mlx->offset[])
			xy_scaled[0] = slope[0] * (xy_loop[0] + mlx->offset[0]);
			xy_scaled[1] = slope[1] * (xy_loop[1] + mlx->offset[1]);
			long double cx = tmpscale(xy_loop[0], (long double[2]){0, WINDOW_WIDTH},
		(long double[2]){-2.0, 1.0});
			long double cy = tmpscale(xy_loop[1], (long double[2]){0, WINDOW_HEIGHT},
		(long double[2]){-1.0, 1.0});
			iter = 0;
			zx = 0.0;
			zy = 0.0;
			//int zx = slope[0] * xy_loop[0];
			//int zy = slope[1] * xy_loop[1];
			while (zx * zx + zy * zy <= 4 && iter < mlx->iter)
			{
				/*//xtemp = zx * zx - zy * zy + xy_scaled[0];
				xtemp = zx * zx - zy * zy + creal + xy_scaled[0];
				zy = 2 * zx * zy + cimag + xy_scaled[1];
				//zy = 2 * zx * zy + xy_scaled[1];
				*/
				xtemp = zx * zy;
				zx=zx*zx-zy*zy+cx + xy_scaled[0];
                zy=2*xtemp+cy + xy_scaled[1];

				iter++;
			}
			if (iter == mlx->iter)
				color = 0;
			else
				color = iter * 0x0000C8;
			pixel_to_image(mlx->image, xy_loop[0], xy_loop[1], color);
			xy_loop[1]++;
		}
		xy_loop[0]++;
	}

}
/*
void	old_mandelbrot(t_mlx *mlx, int px, int py)
{
	long double	xy_scaled[2];
	int		iter;
	int		xy_loop[2];
	long double	x;
	long double	y;
	long double	slope[2];
	int color;
	long double x2;
	long double y2;
	long double w;

	mlx->re1 = -2.0;
	mlx->re2 = 1.0;
	mlx->im1 = -1.0;
	mlx->im2 = 1.0;
	xy_loop[0] = 0;
	xy_loop[1] = 0;

	slope[0] = scale((int[2]){0, WINDOW_WIDTH}, (long double[2]){mlx->re1, mlx->re2});
	slope[1] = scale((int[2]){0, WINDOW_HEIGHT}, (long double[2]){mlx->im1, mlx->im2});
	while (xy_loop[0] < px)
	{
		xy_loop[1] = 0;
		// y loop
		while (xy_loop[1] < py)
		{
			x = 0.0;
			y = 0.0;
			// x loop
			// mouse move offset goes in (xy_loop[] + mlx->offset[])
			xy_scaled[0] = slope[0] * (xy_loop[0] + mlx->offset[0]) * mlx->zoom;
			xy_scaled[1] = slope[1] * (xy_loop[1] + mlx->offset[1]) * mlx->zoom;
			x2 = 0.0;
			y2 = 0.0;
			w = 0.0;
			iter = 0;
			while (x2 + y2 <= 4 && iter < mlx->iter)
			{
				x = (x2 - y2 + xy_scaled[0]);
				y = (w - x2 - y2 + xy_scaled[1]);
				x2 = x * x;
				y2 = y * y;
				w = (x + y) * (x + y);
				iter++;
			}
			if (iter == mlx->iter)
				color = 0;
			else
				color = (DEFAULT_COLOR * iter);
			pixel_to_image(mlx->image, xy_loop[0], xy_loop[1], color);
			xy_loop[1]++;
		}
		xy_loop[0]++;
	}
}
*/
