/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:35:09 by alcohen           #+#    #+#             */
/*   Updated: 2020/03/02 17:14:20 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include "mlx.h"
# include "libft/libft.h"
# include <unistd.h>
# include <math.h>

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 667
# define ZOOM 5
# define DEFAULT_COLOR 0xFFFFFF
# define UP_ARROW 126
# define DOWN_ARROW 125
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define Q 12
# define W 13
# define ERROR_ARGS 1
# define ERROR_MALLOC 2
# define ERROR_READING_FILE 3
# define MAX_ITER 20

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
	int		height;
	int		width;
	void	*init;
	void	*window;
	double	zoom;
	double	zooming;
	int		color;
	int		mouse_x;
	int		mouse_y;
	int		mouse_pressed;
	int		iter;
	t_image	*image;
}				t_mlx;

t_mlx			*initialize_mlx_struct(void);
t_image			*initialize_image(t_mlx *mlx);
int				deal_key(int key, void *param);
int				mouse_event(int button, int x, int y, void *param);
int				mouse_release(int button, int x, int y, void *param);
int				mouse_move(int x, int y, void *param);
void			handle_error(int error);
void			mandelbrot(t_mlx *mlx, int x, int y);
void			handle_drawing(t_mlx *mlx);

#endif
