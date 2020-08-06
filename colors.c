/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:08:32 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/06 16:43:33 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	palette1(int max_iter, int iter)
{
	int	r;
	int	g;
	int	b;

	r = (iter > 25) ? 180 : iter * 7;
	b = (iter > 25) ? 80 : iter * 3;
	g = 20;
	if (iter == max_iter)
		return (0xFFFFFF);
	return (r * 256 * 256 + g * 256 + b);
}

static int	palette2(int max_iter, int iter, int extra[3])
{
	int	r;
	int	g;
	int	b;

	if (iter == max_iter)
		return (0xFFFFFF);
	g = (iter *= 10);
	b = pow(extra[0] > 0 ? extra[0] : -extra[0], 10);
	r = pow(extra[1] > 0 ? extra[1] : -extra[1], 10);
	if (g > 255)
		g = 200 + iter % 55;
	return (r * 256 * 256 + g * 256 + b);
}

static int	palette3(int max_iter, int iter, int extra[3])
{
	int	r;
	int	g;
	int	b;

	if (iter == max_iter)
	{
		r = (extra[2] % 70 - 5);
		g = (extra[2] % 50 - 5);
		b = (extra[2] % 10 + 100);
		return (r * 256 * 256 + g * 256 + b);
	}
	r = (255) * ((extra[2] < WINDOW_WIDTH / 2) ? 1 : 0);
	g = iter < 255 ? ((iter * 3) % 255) : 255;
	b = 100;
	return (r * 256 * 256 + g * 256 + b);
}

static int	palette4(int max_iter, int iter)
{
	int	r;
	int	g;
	int	b;
	int tmp;

	if (iter == max_iter)
		return (0xe6fcfc);
	tmp = iter * 10000;
	g = tmp % 200;
	b = (iter) ^ 255;
	r = (tmp % 256);
	return (r * 256 * 256 + g * 256 + b);
}

int			palette(t_mlx *mlx, int iter, int extra[3])
{
	if (mlx->palette == 1)
		return (palette1(mlx->max_iter, iter));
	if (mlx->palette == 2)
		return (palette2(mlx->max_iter, iter, extra));
	if (mlx->palette == 3)
		return (palette3(mlx->max_iter, iter, extra));
	if (mlx->palette == 4)
		return (palette4(mlx->max_iter, iter));
	return (0);
}
