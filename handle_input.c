/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:03:34 by alcohen           #+#    #+#             */
/*   Updated: 2020/07/31 16:59:22 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				mouse_event(int button, int x, int y, void *param)
{
	t_mlx	*mlx;
	int		w;
	int		h;

	mlx = param;
	if (button == 4)
	{
		h = WINDOW_HEIGHT / 2 - y;
		w = WINDOW_WIDTH / 2 - x;
		mlx->zoom -= ZOOM_AMOUNT;
		mlx->offset[0] += -w * 0.15;
		mlx->offset[1] += -h * 0.15;
		mlx->im1 *= 1.1;
		mlx->im2 *= 1.1;
		mlx->re1 *= 1.1;
		mlx->re2 *= 1.1;
	}
	if (button == 5)
		mlx->zoom += ZOOM_AMOUNT;
	if (button == 1)
	{
		mlx->mouse_x = x;
		mlx->mouse_y = y;
		mlx->mouse_pressed = 1;
	}
	handle_drawing(mlx);
	return (0);
}

int				mouse_release(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	(void)button;
	(void)x;
	(void)y;
	mlx = param;
	mlx->mouse_pressed = 0;
	return (0);
}
#include <stdio.h> //
int				mouse_move(int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (mlx->mouse_pressed && (mlx->fractal == MANDELBROT || \
								mlx->fractal == BURNING_SHIP))
	{
		if (x != mlx->mouse_x)
		{
			mlx->offset[0] -= x - mlx->mouse_x;
		}
		if (y != mlx->mouse_y)
		{
			mlx->offset[1] -= y - mlx->mouse_y;
		}
		handle_drawing(mlx);
	}
	mlx->mouse_x = x;
	mlx->mouse_y = y;
	if (mlx->fractal == JULIA && mlx->mouse_moves >= JULIA_REDRAW_MOVE_AMOUNT)
	{
		mlx->mouse_moves = 0;
		handle_drawing(mlx);
	}
	mlx->mouse_moves++;
	return (0);
}

int				deal_key(int key, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (key == ESC)
		exit(0);
	if (key == UP_ARROW)
		mlx->offset[1] += KEYBOARD_OFFSET_AMOUNT;
	else if (key == DOWN_ARROW)
		mlx->offset[1] -= KEYBOARD_OFFSET_AMOUNT;
	else if (key == LEFT_ARROW)
		mlx->offset[0] += KEYBOARD_OFFSET_AMOUNT;
	else if (key == RIGHT_ARROW)
		mlx->offset[0] -= KEYBOARD_OFFSET_AMOUNT;
	else if (mlx->max_iter > 0 && key == Q)
		mlx->max_iter -= 1;
	else if (key == W)
		mlx->max_iter += 1;
	handle_drawing(mlx);
	return (0);
}
