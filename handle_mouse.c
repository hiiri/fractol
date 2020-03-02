/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:03:34 by alcohen           #+#    #+#             */
/*   Updated: 2020/03/02 19:56:53 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				mouse_event(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (button == 4)
	{
		if (mlx->zoom > 0)
		{
			long double half = WINDOW_HEIGHT / 2;
			long double halfx = WINDOW_WIDTH / 2;
			mlx->zoom -= ZOOM_AMOUNT;
			mlx->offset[0] += (x + 50 - WINDOW_WIDTH * 0.75) / 10;
			mlx->offset[1] += (y - WINDOW_HEIGHT * 0.5) / 10;
			mlx->offset[0] /= 1.1;
			mlx->offset[1] /= 1.1;
			mlx->num1 *= 1.1;
			mlx->num2 *= 1.1;
			mlx->num3 *= 1.1;
			mlx->num4 *= 1.1;
			//printf("%f\n", (x + 50 - WINDOW_WIDTH * 0.75) / 10);
		}
	}
	if (button == 5)
	{
		long double half = WINDOW_HEIGHT / 2;
		long double halfx = WINDOW_WIDTH / 2;
		mlx->zoom += ZOOM_AMOUNT;
		mlx->offset[0] -= ZOOM_AMOUNT;
		mlx->offset[1] -= ZOOM_AMOUNT;
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
			mlx->offset[0] -= 1.0 * x - mlx->mouse_x;
		}
		if (y != mlx->mouse_y)
		{
			mlx->offset[1] -= 1.0 * y - mlx->mouse_y;
		}
	}

	printf("%d %f %Lf\n",mlx->mouse_x, 1.0 * y - mlx->mouse_y, mlx->offset[1]);
	mlx->mouse_x = x;
	mlx->mouse_y = y;
	handle_drawing(mlx);
	return (0);
}
