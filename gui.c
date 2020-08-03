/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:57:17 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/03 18:50:44 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_gui(t_mlx *mlx)
{
	char	*str;
	int		color;

	color = GUI_TEXT_COLOR;
	mlx_string_put(mlx->init, mlx->window, 20, 0, color, "Zoom:");
	str = ft_itoa(mlx->zoom * 10);
	mlx_string_put(mlx->init, mlx->window, 140, 0, color, str);
	free(str);
	mlx_string_put(mlx->init, mlx->window, 20, 20, color, "Iterations:");
	str = ft_itoa(mlx->max_iter);
	mlx_string_put(mlx->init, mlx->window, 140, 20, color, str);
	free(str);
	mlx_string_put(mlx->init, mlx->window, 20, 40, color, "Left mouse button - drag");
	mlx_string_put(mlx->init, mlx->window, 20, 60, color, "Mouse wheel - zoom");
	mlx_string_put(mlx->init, mlx->window, 20, 80, color, "Q - increase iterations");
	mlx_string_put(mlx->init, mlx->window, 20, 100, color, "W - decrease iterations");
	mlx_string_put(mlx->init, mlx->window, 20, 120, color, "Arrow keys - move");
	mlx_string_put(mlx->init, mlx->window, 20, 140, color, "G - toggle GUI");
	mlx_string_put(mlx->init, mlx->window, 20, 160, color, "L - lock mouse (Julia)");
}
