/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:08:32 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/05 16:18:49 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	palette1(int max_iter, int iter, int extra[4])
{
	int	r;
	int	g;
	int	b;
	int tmp;

	if (iter == max_iter)
		return 0xe6fcfc;
	tmp = iter * 10000;
	g = tmp % 200;
	b = (iter) ^ 255;
	r = (tmp % 256);
	return (r * 256 * 256 + g * 256 + b);
}

static int	palette2(int max_iter, int iter, int extra[4])
{
	int	r;
	int	g;
	int	b;

	if (iter == max_iter)
		return 0xFFFFFF;
	g = 0;
	b = pow(extra[0] > 0 ? extra[0] : -extra[0], 10);
	r = pow(extra[1] > 0 ? extra[1] : -extra[1], 10);
	return (r * 256 * 256 + g * 256 + b);
}

int		palette(t_mlx *mlx, int iter, int extra[4])
{
	if (mlx->palette == 1)
		return palette1(mlx->max_iter, iter, extra);
	if (mlx->palette == 2)
		return palette2(mlx->max_iter, iter, extra);
	return 0;
}
