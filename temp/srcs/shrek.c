/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shrek.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmckee <kmckee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:44:04 by kmckee            #+#    #+#             */
/*   Updated: 2018/03/22 23:04:44 by kmckee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	create_strings(t_visual *visual)
{
	visual->win_img = mlx_xpm_file_to_image(visual->mlx,
			"imgs/shrek_win.XPM", &visual->w_win, &visual->h_win);
	visual->shrek_str = (int *)mlx_get_data_addr(visual->shrek_img,
			&visual->shrek_bpp, &visual->shrek_size_line,
			&visual->shrek_endian);
	visual->far_str = (int *)mlx_get_data_addr(visual->far_img,
			&visual->far_bpp, &visual->far_size_line, &visual->far_endian);
	visual->win_str = (int *)mlx_get_data_addr(visual->win_img,
			&visual->win_bpp, &visual->win_size_line, &visual->win_endian);
}

void	shrek_init(t_visual *visual)
{
	if (visual->size == 75)
	{
		visual->shrek_img = mlx_xpm_file_to_image(visual->mlx,
				"imgs/shrek_large.XPM", &visual->w_shrek, &visual->h_shrek);
		visual->far_img = mlx_xpm_file_to_image(visual->mlx,
				"imgs/farquaad_large.XPM", &visual->w_far, &visual->h_far);
	}
	else if (visual->size == 40)
	{
		visual->shrek_img = mlx_xpm_file_to_image(visual->mlx,
				"imgs/shrek_medium.XPM", &visual->w_shrek, &visual->h_shrek);
		visual->far_img = mlx_xpm_file_to_image(visual->mlx,
				"imgs/farquaad_medium.XPM", &visual->w_far, &visual->h_far);
	}
	else
	{
		visual->shrek_img = mlx_xpm_file_to_image(visual->mlx,
				"imgs/shrek_small.XPM", &visual->w_shrek, &visual->h_shrek);
		visual->far_img = mlx_xpm_file_to_image(visual->mlx,
				"imgs/farquaad_small.XPM", &visual->w_far, &visual->h_far);
	}
	create_strings(visual);
}

void	draw_win(t_visual *visual)
{
	put_piece(0, 0);
	mlx_destroy_image(visual->mlx, visual->img);
	visual->win_img = mlx_xpm_file_to_image(visual->mlx,
			"imgs/shrek_win.XPM", &visual->w_win, &visual->h_win);
	visual->win_str = (int *)mlx_get_data_addr(visual->win_img,
			&visual->win_bpp, &visual->win_size_line, &visual->win_endian);
	mlx_put_image_to_window(visual->mlx, visual->win,
			visual->win_img, (visual->width / 2) - (visual->w_win / 2),
			(visual->height / 2) - (visual->h_win / 2));
	mlx_do_sync(visual->mlx);
	sleep(5);
	exit(0);
}
