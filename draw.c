/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:34:51 by alcohen           #+#    #+#             */
/*   Updated: 2020/06/01 17:03:15 by alcohen          ###   ########.fr       */
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
	//if type == mandelbrot
	mandelbrot(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_put_image_to_window(mlx->init, mlx->window, mlx->image->img_ptr, 0, 0);
}

void	mandelbrot(t_mlx *mlx, int px, int py)
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

	mlx->num1 = -2.0;
	mlx->num2 = 1.0;
	mlx->num3 = -1.0;
	mlx->num4 = 1.0;
	xy_loop[0] = 0;
	xy_loop[1] = 0;

	slope[0] = scale((int[2]){0, WINDOW_WIDTH}, (long double[2]){mlx->num1, mlx->num2});
	slope[1] = scale((int[2]){0, WINDOW_HEIGHT}, (long double[2]){mlx->num3, mlx->num4});
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
				y = (w - x2 - y2 + xy_scaled[1]) ;
				x2 = x * x;
				y2 = y * y;
				w = (x + y) * (x + y);
				iter++;
			}
			if (iter == mlx->iter)
				color = 0;
			else
				color = (0x00F0F * iter);
			pixel_to_image(mlx->image, xy_loop[0], xy_loop[1], color);
			//mlx_pixel_put(mlx, mlx->window, xy_loop[0], xy_loop[1], color);
			xy_loop[1]++;
		}
		xy_loop[0]++;
	}
}
