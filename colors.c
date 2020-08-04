/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:08:32 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/04 16:42:32 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		palette(t_mlx *mlx, int iter)
{
	int	max;
	int	r;
	int	g;
	int	b;

	if (iter < 4)
		return 0;
	r = 80 * iter;
	g = 80 * iter;
	b = (iter) ^ 255;
	max = mlx->max_iter;

	return (int)(r * 256 * 256 + g + b);
}

