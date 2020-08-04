/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:08:32 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/04 18:39:14 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	palette1(int max_iter, int iter)
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

static int	palette2(int max_iter, int iter)
{
	int	r;
	int	g;
	int	b;

	if (iter == max_iter)
		return 0;
	g = 0;
	b = (iter * 1000) % 255;
	r = 10;
	return (r * 256 * 256 + g * 256 + b);
}

int		palette(t_mlx *mlx, int iter)
{
	if (mlx->palette == 1)
		return palette1(mlx->max_iter, iter);
	if (mlx->palette == 2)
		return palette2(mlx->max_iter, iter);
	return 0;
}
