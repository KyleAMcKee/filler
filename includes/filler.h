/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmckee <kmckee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 11:41:29 by kmckee            #+#    #+#             */
/*   Updated: 2018/03/23 17:24:41 by kmckee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"

typedef struct	s_map {
	char		player;
	char		opponent;
	int			height;
	int			width;
	char		**map;
	char		**piece;
	char		**new_piece;
	int			**heat_map;
	int			h_piece;
	int			w_piece;
	int			x_offset;
	int			y_offset;
	int			score;
	int			x_print;
	int			y_print;
	int			valid;
	int			stars;
	int			min_x;
	int			min_y;
	int			max_x;
	int			max_y;
	int			star;
}				t_map;

typedef	struct	s_visual {
	void		*mlx;
	void		*win;
	void		*img;
	int			*pixel_str;
	int			bbp;
	int			size_line;
	int			endian;
	int			height;
	int			width;
	int			size;
	void		*shrek_img;
	void		*far_img;
	void		*win_img;
	int			w_shrek;
	int			h_shrek;
	int			w_far;
	int			h_far;
	int			w_win;
	int			h_win;
	int			*shrek_str;
	int			*far_str;
	int			*win_str;
	int			shrek_bpp;
	int			shrek_size_line;
	int			shrek_endian;
	int			far_bpp;
	int			far_size_line;
	int			far_endian;
	int			win_bpp;
	int			win_size_line;
	int			win_endian;
}				t_visual;

/*
**	ALGO
*/

void			algorithm(t_map *map, t_visual *visual);
int				check_piece(t_map *map, int j, int i);
void			find_first_star(t_map *map);

/*
**	HEAT MAP
*/

void			heat_init(t_map *map);
void			heat_convert(t_map *map);
void			heat_populate(t_map *map, int y, int x);
void			heat_calculate(t_map *map);
void			heat_find(t_map *map);

/*
**	UTILITIES
*/

void			free_everything(t_map *map);
void			put_piece(int y, int x);

/*
**  RESIZE PIECE
*/

void			get_offset(t_map *map);
void			make_piece(t_map *map);
void			resize_piece(t_map *map);

/*
**  VISUALIZER
*/

void			gfx_map_init(t_visual *visual, t_map *map);
void			create_map(t_visual *visual);
void			draw_map(t_map *map, t_visual *visual);

/*
**  SHREK MODE
*/

void			shrek_init(t_visual *visual);
void			draw_win(t_visual *visual);

#endif
