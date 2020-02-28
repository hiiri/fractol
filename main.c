/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:35:05 by alcohen           #+#    #+#             */
/*   Updated: 2020/02/28 20:32:47 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fractol.h"

t_mlx			*initialize_mlx_struct(void)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(*mlx))))
		handle_error(ERROR_MALLOC);
	mlx->height = WINDOW_HEIGHT;
	mlx->width = WINDOW_WIDTH;
	mlx->zoom = ZOOM;
	mlx->color = DEFAULT_COLOR;
	mlx->mouse_x = 0;
	mlx->mouse_y = 0;
	mlx->mouse_pressed = 0;
	mlx->zoom = 1;
	mlx->iter = MAX_ITER;
	return (mlx);
}

int				deal_key(int key, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (key == 53)
		exit(0);
	if (key == UP_ARROW)
	 	mlx->zoom += 0.01;
	else if (key == DOWN_ARROW)
		mlx->zoom -= 0.01;
	// else if (key == LEFT_ARROW)
	// 	mlx->x_offset -= OFFSET_AMOUNT;
	// else if (key == RIGHT_ARROW)
	// 	mlx->x_offset += OFFSET_AMOUNT;
	// else if (key == Q)
	// 	mlx->pitch -= PITCH_CHANGE_AMOUNT;
	// else if (key == W)
	// 	mlx->pitch += PITCH_CHANGE_AMOUNT;
	mandelbrot(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	return (0);
}

void			handle_error(int error)
{
	if (error == ERROR_ARGS)
		write(1, "Argument count must be 1\n", 25);
	else if (error == ERROR_MALLOC)
		write(1, "Malloc error\n", 13);
	else if (error == ERROR_READING_FILE)
		write(1, "Couldn't read file\n", 19);
	exit(0);
}

int				main(int argc, char **argv)
{
	t_mlx	*mlx;

	(void)argv;
	(void)argc;
	// if (argc != 2)
	// 	handle_error(1);
	mlx = initialize_mlx_struct();
	mlx->init = mlx_init();
	mlx->window = mlx_new_window(mlx->init, mlx->width, mlx->height, "Window");
	mlx_hook(mlx->window, 2, 0, deal_key, mlx);
	mlx_hook(mlx->window, 4, 0, mouse_event, mlx);
	// mlx_hook(mlx->window, 5, 0, mouse_release, mlx);
	// mlx_hook(mlx->window, 6, 0, mouse_move, mlx);
	mandelbrot(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_loop(mlx->init);
	return (0);
}
