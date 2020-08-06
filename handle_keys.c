/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:26:04 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/06 16:32:07 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		change_palette(t_mlx *mlx)
{
	if (mlx->palette == PALETTE_COUNT)
		mlx->palette = 1;
	else
		mlx->palette++;
}


int				deal_key(int key, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (key == ESC)
		exit(0);


	if (key == UP_ARROW || key == DOWN_ARROW)
		mlx->offset[1] += (key == UP_ARROW ? KB_OFFSET_AMOUNT : -KB_OFFSET_AMOUNT);
	else if (key == LEFT_ARROW || key == RIGHT_ARROW)
		mlx->offset[0] += (key == LEFT_ARROW ? KB_OFFSET_AMOUNT : -KB_OFFSET_AMOUNT);
	else if (mlx->max_iter > 0 && key == Q)
		mlx->max_iter -= 1;
	else if (key == W)
		mlx->max_iter += 1;
	else if (key == G)
		mlx->gui_on ^= 1;
	else if (key == R)
		reset_view(mlx);
	else if (key == L)
		mlx->lock_mouse ^= 1;
	else if (key == E)
		change_palette(mlx);
	handle_drawing(mlx);
	return (0);
}

void		reset_view(t_mlx *mlx)
{
	mlx->color = DEFAULT_COLOR;
	mlx->zoom = INIT_ZOOM_SCALE;
	if (mlx->fractal == MANDELBROT)
	{
		mlx->offset[0] = INIT_MANDELBROT_OFFSET_X;
		mlx->offset[1] = INIT_MANDELBROT_OFFSET_Y;
	}
	else if (mlx->fractal == JULIA)
	{
		mlx->offset[0] = INIT_JULIA_OFFSET_X;
		mlx->offset[1] = INIT_JULIA_OFFSET_Y;
	}
	else if (mlx->fractal == BURNING_SHIP)
	{
		mlx->offset[0] = INIT_BURNING_SHIP_OFFSET_X;
		mlx->offset[1] = INIT_BURNING_SHIP_OFFSET_Y;
	}
}

