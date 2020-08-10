/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:59:10 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/10 19:02:29 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	calculate_julia_mouse_params(t_mlx *mlx)
{
	mlx->julia_mov[0] = -0.8 + 0.6 * sin(mlx->mouse_x / (3.14 * 100));
	mlx->julia_mov[1] = 0.156 + 0.4 * cos(mlx->mouse_y / (3.14 * 20));
}

static void	calculate_julia_numbers(t_mlx *mlx, int xy[2], long double new[2])
{
	new[0] = 1.5 * (xy[0] - WINDOW_WIDTH / 2) /
		(0.5 * WINDOW_WIDTH) +
		((mlx->offset[0] * 0.001));
	new[1] = (xy[1] - WINDOW_HEIGHT / 2) /
			(0.5 * WINDOW_HEIGHT) +
			((mlx->offset[1] * 0.001));
	new[0] *= mlx->zoom;
	new[1] *= mlx->zoom;
}

static int	color(t_mlx *mlx, int i, long double new[2], int xy[2])
{
	return (palette(mlx, i, (int[3]){new[0], new[1], xy[0]}));
}

static void	julia_loop(t_mlx *mlx, long double new[2])
{
	long double	old_re;
	long double	old_im;

	old_re = new[0];
	old_im = new[1];
	new[0] = old_re * old_re - old_im * old_im + mlx->julia_mov[0];
	new[1] = 2 * old_re * old_im + mlx->julia_mov[1];
}

void		julia(t_thread *td, t_mlx *mlx, int px, int py)
{
	int			i;
	int			xy[2];
	long double new[2];

	xy[0] = WINDOW_WIDTH / MAX_THREADS * td->num;
	xy[1] = 0;
	if (!mlx->lock_mouse)
		calculate_julia_mouse_params(mlx);
	while (xy[0] < px)
	{
		xy[1] = 0;
		while (xy[1] < py)
		{
			calculate_julia_numbers(mlx, xy, new);
			i = 0;
			while (new[0] * new[0] + new[1] * new[1] < 4 && i < mlx->max_iter)
			{
				julia_loop(mlx, new);
				i++;
			}
			px_to_img(mlx->image, xy[0], xy[1], color(mlx, i, new, xy));
			xy[1]++;
		}
		xy[0]++;
	}
}
