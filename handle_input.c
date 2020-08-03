/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:03:34 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/03 18:51:13 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		reset_view(t_mlx *mlx)
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

int				mouse_event(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (button == 4 && mlx->zoom > MIN_ZOOM)
	{
		mlx->zoom -= ZOOM_AMOUNT;
	}
	if (button == 5)
	{
		mlx->zoom += ZOOM_AMOUNT;
	}
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

int				mouse_move(int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (mlx->mouse_pressed)
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
	if (mlx->fractal == JULIA && !mlx->lock_mouse)
	{
		handle_drawing(mlx);
	}
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
	else if (key == G)
		mlx->gui_on ^= 1;
	else if (key == R)
		reset_view(mlx);
	else if (key == L)
		mlx->lock_mouse ^= 1;
	handle_drawing(mlx);
	return (0);
}
