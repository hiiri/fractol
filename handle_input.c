/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:03:34 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/05 18:47:31 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				mouse_event(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (button == 4 && mlx->zoom > MIN_ZOOM)
	{
		mlx->offset[0] += (WINDOW_WIDTH * 0.5 - x) ;
		mlx->offset[1] += (WINDOW_HEIGHT * 0.5 - y);
		printf("%f\n", (WINDOW_WIDTH * 0.5 - x));
		mlx->zoom -= pow(ZOOM_AMOUNT, 0.5);
	}
	if (button == 5)
	{
		mlx->offset[0] -= (WINDOW_WIDTH * 0.5 - x) ;
		mlx->offset[1] -= (WINDOW_HEIGHT * 0.5 - y);
		mlx->zoom += pow(ZOOM_AMOUNT, 0.5);
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
