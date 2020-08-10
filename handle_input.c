/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:03:34 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/10 19:33:02 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			handle_zoom(t_mlx *mlx, int button, int x, int y)
{
	if (button == 4 && mlx->zoom > MAX_ZOOM)
	{
		mlx->zoom /= 1.1;
		mlx->offset[0] = (mlx->offset[0] +
			(x - WINDOW_WIDTH / 2) * 0.25) * 1.1 + 60;
		mlx->offset[1] = (mlx->offset[1] +
			(y - WINDOW_HEIGHT / 2) * 0.25) * 1.1 + 40;
	}
	if (button == 5 && mlx->zoom < MIN_ZOOM)
	{
		mlx->zoom *= 1.1;
		mlx->offset[0] = (mlx->offset[0] +
			(x - WINDOW_WIDTH / 2) * 0.25) / 1.1 - 60;
		mlx->offset[1] = (mlx->offset[1] +
			(y - WINDOW_HEIGHT / 2) * 0.25) / 1.1 - 40;
	}
}

int				mouse_event(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (button == 4 || button == 5)
		handle_zoom(mlx, button, x, y);
	if (button == 1)
	{
		mlx->mouse_x = x;
		mlx->mouse_y = y;
		mlx->mouse_pressed = 1;
	}
	if (button == 2)
	{
		mlx->zoom /= 1.3;
		mlx->offset[0] = (mlx->offset[0] + (x - WINDOW_WIDTH / 2)) * 1.3 + 160;
		mlx->offset[1] = (mlx->offset[1] + (y - WINDOW_HEIGHT / 2)) * 1.3 + 160;
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
			mlx->offset[0] -= x - mlx->mouse_x;
		if (y != mlx->mouse_y)
			mlx->offset[1] -= y - mlx->mouse_y;
		handle_drawing(mlx);
	}
	mlx->mouse_x = x;
	mlx->mouse_y = y;
	if (mlx->fractal == JULIA && !mlx->lock_mouse)
		handle_drawing(mlx);
	return (0);
}
