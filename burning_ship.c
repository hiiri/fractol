/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:35:15 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/11 17:41:32 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int			bs_loop(t_mlx *mlx, long double xy_scaled[2])
{
	long double	zx;
	long double	zy;
	long double	xtemp;
	int			iter;

	iter = 0;
	zx = 0;
	zy = 0;
	xtemp = 0;
	while (zx * zx + zy * zy < 4 && iter < mlx->max_iter)
	{
		xtemp = zx * zx - zy * zy + xy_scaled[0];
		zy = fabsl(2 * zx * zy + xy_scaled[1]);
		zx = fabsl(xtemp);
		iter++;
	}
	return (iter);
}

void				burning_ship(t_thread *td, t_mlx *mlx, int px, int py)
{
	long double	scaled[2];
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
			scaled[0] = (slope[0] * (xy_loop[0] + mlx->offset[0])) * mlx->zoom;
			scaled[1] = (slope[1] * (xy_loop[1] + mlx->offset[1])) * mlx->zoom;
			px_to_img(mlx->image, xy_loop[0], xy_loop[1],
						palette(mlx, bs_loop(mlx, scaled),
						(int[3]){1, 1, xy_loop[0]}));
			xy_loop[1]++;
		}
		xy_loop[0]++;
	}
}
