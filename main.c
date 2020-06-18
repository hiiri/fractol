/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:35:05 by alcohen           #+#    #+#             */
/*   Updated: 2020/06/01 19:17:36 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fractol.h"

t_image			*initialize_image(t_mlx *mlx)
{
	t_image	*image;

	if (!(image = (t_image*)malloc(sizeof(*image))))
		handle_error(ERROR_MALLOC);
	image->width = WINDOW_WIDTH;
	image->height = WINDOW_HEIGHT;
	image->bpp = 0;
	image->endian = 0;
	image->size_line = 0;
	image->img_ptr = mlx_new_image(mlx->init, image->width, image->height);
	image->image = mlx_get_data_addr(image->img_ptr, &image->bpp, &image->size_line, &image->endian);
	return (image);
}

t_mlx			*initialize_mlx_struct(void)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(*mlx))))
		handle_error(ERROR_MALLOC);
	mlx->height = WINDOW_HEIGHT;
	mlx->width = WINDOW_WIDTH;
	mlx->fractal = MANDELBROT;
	mlx->color = DEFAULT_COLOR;
	mlx->mouse_x = 0;
	mlx->mouse_y = 0;
	mlx->mouse_pressed = 0;
	mlx->zoom = INIT_ZOOM_SCALE;
	mlx->offset[0] = INIT_OFFSET_X;
	mlx->offset[1] = INIT_OFFSET_Y;
	mlx->iter = MAX_ITER;
	mlx->mouse_moves = 0;
	return (mlx);
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
	else if (mlx->iter > 0 && key == Q)
		mlx->iter -= 1;
	else if (key == W)
		mlx->iter += 1;
	handle_drawing(mlx);
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
	mlx->image = initialize_image(mlx);

	mlx->window = mlx_new_window(mlx->init, mlx->width, mlx->height, "Window");
	mlx_hook(mlx->window, 2, (1L<<0), deal_key, mlx);
	mlx_hook(mlx->window, 4, (1L<<2), mouse_event, mlx);
	mlx_hook(mlx->window, 5, 0, mouse_release, mlx);
	mlx_hook(mlx->window, 6, (1L<<6), mouse_move, mlx);
	handle_drawing(mlx);
	mlx_loop(mlx->init);
	return (0);
}
