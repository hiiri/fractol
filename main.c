/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:35:05 by alcohen           #+#    #+#             */
/*   Updated: 2020/07/31 17:23:35 by alcohen          ###   ########.fr       */
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
	image->img_ptr = mlx_new_image(mlx->init, image->width, image->height);
	image->image = mlx_get_data_addr(image->img_ptr, &image->bpp, \
									&image->size_line, &image->endian);
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
	mlx->max_iter = MAX_ITER;
	return (mlx);
}

void			handle_error(int error)
{
	if (error == ERROR_ARGS)
	{
		ft_putstr("Usage: ./fractol [type]\n");
		ft_putstr("Available parameters: mandelbrot, julia, burning_ship\n");
	}
	else if (error == ERROR_MALLOC)
		ft_putstr("Malloc error\n");
	else if (error == ERROR_READING_FILE)
		ft_putstr("Couldn't read file\n");
	else if (error == ERROR_CREATING_THREAD)
		ft_putstr("Error creating thread\n");
	exit(0);
}

static int		check_arguments(char *arg)
{
	if (ft_strcmp("mandelbrot", arg) == 0)
		return (MANDELBROT);
	if (ft_strcmp("julia", arg) == 0)
		return (JULIA);
	if (ft_strcmp("burning_ship", arg) == 0)
		return (BURNING_SHIP);
	return (-1);
}

int				main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (argc == 2)
	{
		mlx = initialize_mlx_struct();
		if ((mlx->fractal = check_arguments(argv[1])) == -1)
			handle_error(ERROR_ARGS);
		mlx->init = mlx_init();
		mlx->image = initialize_image(mlx);
		mlx->window = mlx_new_window(mlx->init, mlx->width, \
									mlx->height, "Fractol");
		mlx_hook(mlx->window, 2, (1L << 0), deal_key, mlx);
		mlx_hook(mlx->window, 4, (1L << 2), mouse_event, mlx);
		mlx_hook(mlx->window, 5, (1L << 3), mouse_release, mlx);
		mlx_hook(mlx->window, 6, (1L << 6), mouse_move, mlx);
		handle_drawing(mlx);
		mlx_loop(mlx->init);
	}
	else
		handle_error(ERROR_ARGS);
	return (0);
}
