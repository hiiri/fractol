/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:59:10 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/06 17:08:55 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			calculate_julia_mouse_params(t_mlx *mlx)
{
	mlx->julia_mouse_params[0] = -0.8 + 0.6 * sin(mlx->mouse_x / (3.14 * 100));
	mlx->julia_mouse_params[1] = 0.156 + 0.4 * cos(mlx->mouse_y / (3.14 * 20));
}

static void			calculate_julia_numbers(t_mlx *mlx, int xy_loop[2], long double new_re_im[2])
{
	new_re_im[0] = 1.5 * (xy_loop[0] - WINDOW_WIDTH / 2) / (0.5 * pow(mlx->zoom, 3) * WINDOW_WIDTH) + ((mlx->offset[0] * 0.001) / mlx->zoom);
	new_re_im[1] = (xy_loop[1] - WINDOW_HEIGHT / 2) / (0.5 * pow(mlx->zoom, 3) * WINDOW_HEIGHT) + ((mlx->offset[1] * 0.001) / mlx->zoom);
}

void				julia(t_thread *td, t_mlx *mlx, int px, int py)
{
	int			iter;
	int			xy_loop[2];
	int			color;
	// long double	new_re;
	// long double	new_im;
	long double	old_re;
	long double	old_im;
	long double new_re_im[2];
	//long double old_re_im[2];


	xy_loop[0] = WINDOW_WIDTH / MAX_THREADS * td->num;
	xy_loop[1] = 0;
	if (!mlx->lock_mouse)
		calculate_julia_mouse_params(mlx);
	while (xy_loop[0] < px)
	{
		xy_loop[1] = 0;
		while (xy_loop[1] < py)
		{
			calculate_julia_numbers(mlx, xy_loop, new_re_im);
			iter = 0;
			while (new_re_im[0] * new_re_im[0] + new_re_im[1] * new_re_im[1] < 4 && iter < mlx->max_iter)
			{
				old_re = new_re_im[0];
				old_im = new_re_im[1];
				new_re_im[0] = old_re * old_re - old_im * old_im + mlx->julia_mouse_params[0];
				new_re_im[1] = 2 * old_re * old_im + mlx->julia_mouse_params[1];
				iter++;
			}
			color = palette(mlx, iter, (int[3]){new_re_im[0], new_re_im[1], xy_loop[0]});
			pixel_to_image(mlx->image, xy_loop[0], xy_loop[1], color);
			xy_loop[1]++;
		}
		xy_loop[0]++;
	}
}
