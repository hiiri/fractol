/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:57:17 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/04 16:05:00 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	display_string(t_mlx *mlx, int x, int y, char *str)
{
	mlx_string_put(mlx->init, mlx->window, x, y, GUI_TEXT_COLOR, str);
}

void		draw_gui(t_mlx *mlx)
{
	char	*str;

	display_string(mlx, 20, 0, "Zoom:");
	str = ft_itoa(mlx->zoom * 10);
	display_string(mlx, 140, 0, str);
	free(str);
	display_string(mlx, 20, 20, "Iterations:");
	str = ft_itoa(mlx->max_iter);
	display_string(mlx, 140, 20, str);
	free(str);
	display_string(mlx, 20, 40, "Left mouse button - drag");
	display_string(mlx, 20, 60, "Mouse wheel - zoom");
	display_string(mlx, 20, 80, "Q - increase iterations");
	display_string(mlx, 20, 100, "W - decrease iterations");
	display_string(mlx, 20, 120, "Arrow keys - move");
	display_string(mlx, 20, 140, "G - toggle GUI");
	display_string(mlx, 20, 160, "L - lock mouse (Julia)");
	display_string(mlx, 20, 180, "R - reset view");
}
