/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:35:09 by alcohen           #+#    #+#             */
/*   Updated: 2020/08/06 16:39:12 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include "libft/libft.h"
# include <unistd.h>
# include <math.h>
# include <pthread.h>

/*
** Keys
*/

# ifdef __APPLE__
#  include "mlx.h"
#  define UP_ARROW 126
#  define DOWN_ARROW 125
#  define LEFT_ARROW 123
#  define RIGHT_ARROW 124
#  define Q 12
#  define W 13
#  define G 5
#  define R 15
#  define L 37
#  define E 14
#  define ESC 53
# elif __linux__
#  include "../minilibx/mlx.h"
#  define UP_ARROW 65362
#  define DOWN_ARROW 65364
#  define LEFT_ARROW 65361
#  define RIGHT_ARROW 65363
#  define Q 113
#  define W 119
#  define ESC 65307
# endif

/*
** General
*/

# define DEFAULT_COLOR 0x0F000F
# define INIT_MANDELBROT_OFFSET_X -800
# define INIT_MANDELBROT_OFFSET_Y -390
# define INIT_JULIA_OFFSET_X 0
# define INIT_JULIA_OFFSET_Y 0
# define INIT_BURNING_SHIP_OFFSET_X -800
# define INIT_BURNING_SHIP_OFFSET_Y -500
# define KB_OFFSET_AMOUNT 50
# define MAX_ITER 10
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 800
# define ZOOM_AMOUNT 0.001
# define MIN_ZOOM 0.001
# define INIT_ZOOM_SCALE 0.9
# define GUI_TEXT_COLOR 0xFFFFFF
# define PALETTE_COUNT 4

/*
** Multithreading
*/

# define MAX_THREADS 12

/*
** Fractals
*/

# define MANDELBROT 1
# define JULIA 2
# define BURNING_SHIP 3

/*
**	Error messages
*/

# define ERROR_ARGS 1
# define ERROR_MALLOC 2
# define ERROR_READING_FILE 3
# define ERROR_FRACTAL_TYPE 4
# define ERROR_CREATING_THREAD 5

typedef struct	s_image
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
	int			gui_on;
	int			lock_mouse;
	long double	julia_mouse_params[2];
	long double	re1;
	long double	re2;
	long double	im1;
	long double	im2;
	int			palette;
	t_image		*image;
}				t_mlx;

typedef struct	s_thread
{
	int		size;
	int		num;
	t_mlx	*mlx;
}				t_thread;

t_mlx			*initialize_mlx_struct(void);
t_image			*initialize_image(t_mlx *mlx);
int				deal_key(int key, void *param);
int				mouse_event(int button, int x, int y, void *param);
int				mouse_release(int button, int x, int y, void *param);
int				mouse_move(int x, int y, void *param);
void			handle_error(int error);
void			mandelbrot(t_thread *td, t_mlx *mlx, int px, int py);
void			julia(t_thread *td, t_mlx *mlx, int px, int py);
void			burning_ship(t_thread *td, t_mlx *mlx, int x, int y);
void			handle_drawing(t_mlx *mlx);
void			draw_gui(t_mlx *mlx);
int				palette(t_mlx *mlx, int iter, int extra[3]);
void			reset_view(t_mlx *mlx);

#endif
