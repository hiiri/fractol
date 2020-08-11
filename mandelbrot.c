/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:35:17 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/11 17:06:35 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int			mb_loop(t_mlx *mlx, long double xy_scaled[2])
{
	long double	xy[2];
	long double	xy2[2];
	long double	w;
	int			iter;

	xy[0] = 0.0;
	xy[1] = 0.0;
	xy2[0] = 0.0;
	xy2[1] = 0.0;
	w = 0.0;
	iter = 0;
	while (xy2[0] + xy2[1] <= 4 && iter < mlx->max_iter)
	{
		xy[0] = (xy2[0] - xy2[1] + xy_scaled[0]);
		xy[1] = (w - xy2[0] - xy2[1] + xy_scaled[1]);
		xy2[0] = xy[0] * xy[0];
		xy2[1] = xy[1] * xy[1];
		w = (xy[0] + xy[1]) * (xy[0] + xy[1]);
		iter++;
	}
	return (iter);
}

void				mandelbrot(t_thread *td, t_mlx *mlx, int px, int py)
{
	long double	xy_scaled[2];
	int			xy_loop[2];
	long double	slope[2];

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
			xy_scaled[0] = slope[0] * (xy_loop[0] + mlx->offset[0]) * mlx->zoom;
			xy_scaled[1] = slope[1] * (xy_loop[1] + mlx->offset[1]) * mlx->zoom;
			px_to_img(mlx->image, xy_loop[0], xy_loop[1],
						palette(mlx, mb_loop(mlx, xy_scaled),
						(int[3]){1, 1, xy_loop[0]}));
			xy_loop[1]++;
		}
		xy_loop[0]++;
	}
}
