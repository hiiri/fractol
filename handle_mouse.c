/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:03:34 by alcohen           #+#    #+#             */
/*   Updated: 2020/06/01 19:00:05 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h> //remove


int				mouse_event(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (button == 4)
	{
		if (mlx->zoom > 0)
		{
			int h = WINDOW_HEIGHT / 2;
			int w = WINDOW_WIDTH / 2;

			h = h - y;
			w = w - x;
			//h /= mlx->zoom;
			//w /= mlx->zoom;
			//printf("%Lf %Lf, %Lf\n", h, w, mlx->zoom);
			//printf("%Lf %Lf, %Lf\n", mlx->offset[0], mlx->offset[0], mlx->zoom);
			mlx->zoom -= ZOOM_AMOUNT;

			mlx->offset[0] += -w * 0.15;
			mlx->offset[1] += -h * 0.15;

			//mlx->offset[0] += (x + 50 - WINDOW_WIDTH * 0.75) / 10;
			//mlx->offset[1] += (y - WINDOW_HEIGHT * 0.5) / 10;
			//mlx->offset[0] /= 1.1;
			//mlx->offset[1] /= 1.1;
			mlx->im1 *= 1.1;
			mlx->im2 *= 1.1;
			mlx->re1 *= 1.1;
			mlx->re2 *= 1.1;
			//printf("%f\n", (x + 50 - WINDOW_WIDTH * 0.75) / 10);
		}
	}
	if (button == 5)
	{
		//long double half = WINDOW_HEIGHT / 2;
		//long double halfx = WINDOW_WIDTH / 2;
		mlx->zoom += ZOOM_AMOUNT;
	}
	//this is only to set mouse pressed to 1, mouse move is its own function
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
	if (mlx->mouse_pressed && mlx->fractal == MANDELBROT)
	{
		if (x != mlx->mouse_x)
		{
			mlx->offset[0] -= 1.0 * x - mlx->mouse_x;
		}
		if (y != mlx->mouse_y)
		{
			mlx->offset[1] -= 1.0 * y - mlx->mouse_y;
		}
		handle_drawing(mlx);
	}
	mlx->mouse_x = x;
	mlx->mouse_y = y;
	if (mlx->fractal == JULIA && mlx->mouse_moves >= JULIA_REDRAW_EVERY_MOUSE_MOVE_AMOUNT)
	{
		mlx->mouse_moves = 0;
		handle_drawing(mlx);
	}
	mlx->mouse_moves++;
	return (0);
}
