/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:35:09 by alcohen           #+#    #+#             */
/*   Updated: 2020/07/30 16:41:04 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include "libft/libft.h"
# include <unistd.h>
# include <math.h>

/*
** Keys
*/

# ifdef __APPLE__
	# include "mlx.h"
	# define UP_ARROW 126
	# define DOWN_ARROW 125
	# define LEFT_ARROW 123
	# define RIGHT_ARROW 124
	# define Q 12
	# define W 13
	# define ESC 53
# elif __linux__
	# include "../minilibx/mlx.h"
	# define UP_ARROW 65362
	# define DOWN_ARROW 65364
	# define LEFT_ARROW 65361
	# define RIGHT_ARROW 65363
	# define Q 113
	# define W 119
	# define ESC 65307
	# endif

/*
** General
*/

# define DEFAULT_COLOR 0x0F000F
# define INIT_OFFSET_X -700
# define INIT_OFFSET_Y -320
# define KEYBOARD_OFFSET_AMOUNT 50
# define MAX_ITER 10
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 800
# define ZOOM_AMOUNT 0.1
# define INIT_ZOOM_SCALE 1

/*
** Fractals
*/

# define MANDELBROT 1
# define JULIA 2
# define BURNING_SHIP 3
/*
** Performance
*/

# define JULIA_REDRAW_EVERY_MOUSE_MOVE_AMOUNT 1

/*
**	Error messages
*/

# define ERROR_ARGS 1
# define ERROR_MALLOC 2
# define ERROR_READING_FILE 3
# define ERROR_FRACTAL_TYPE 4

typedef struct s_image
{
	int			width;
	int			height;
	char		*image;
	int			bpp;
	int			size_line;
	int			endian;
	void		*img_ptr;
}				t_image;

typedef struct	s_mlx
{
	int			mouse_moves;
	int			height;
	int			width;
	void		*init;
	void		*window;
	int			fractal;
	long double	zoom;
	int			offset[2];
	int			color;
	int			mouse_x;
	int			mouse_y;
	int			mouse_pressed;
	int			max_iter;
	long double	re1;
	long double	re2;
	long double	im1;
	long double	im2;
	t_image		*image;
}				t_mlx;

t_mlx			*initialize_mlx_struct(void);
t_image			*initialize_image(t_mlx *mlx);
int				deal_key(int key, void *param);
int				mouse_event(int button, int x, int y, void *param);
int				mouse_release(int button, int x, int y, void *param);
int				mouse_move(int x, int y, void *param);
void			handle_error(int error);
void			mandelbrot(t_mlx *mlx, int px, int py);
void			julia(t_mlx *mlx, int px, int py);
void			burning_ship(t_mlx *mlx, int x, int y);
void			handle_drawing(t_mlx *mlx);

#endif
