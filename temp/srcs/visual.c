/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmckee <kmckee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 09:00:06 by kmckee            #+#    #+#             */
/*   Updated: 2018/03/22 21:24:27 by kmckee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	create_map(t_visual *visual)
{
	visual->img = mlx_new_image(visual->mlx, visual->width,
			visual->height);
	visual->pixel_str = (int *)mlx_get_data_addr(visual->img,
			&visual->bbp, &visual->size_line,
			&visual->endian);
}

void	drawsquare(t_visual *visual, int index, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < visual->size)
	{
		j = -1;
		while (++j < visual->size)
		{
			if (j == 0 || i == 0)
				visual->pixel_str[index++] = 0x000000;
			else
				visual->pixel_str[index++] = color;
		}
		index += visual->width - visual->size;
	}
}

void	draw_shrek(t_visual *visual, int index)
{
	int i;
	int j;

	i = -1;
	while (++i < visual->size)
	{
		j = -1;
		while (++j < visual->size)
		{
			if (j == 0 || i == 0)
				visual->pixel_str[index++] = 0x000000;
			else
				visual->pixel_str[index++] =
					visual->shrek_str[(visual->h_shrek * i) + j];
		}
		index += visual->width - visual->size;
	}
}

void	draw_farquaad(t_visual *visual, int index)
{
	int i;
	int j;

	i = -1;
	while (++i < visual->size)
	{
		j = -1;
		while (++j < visual->size)
		{
			if (j == 0 || i == 0)
				visual->pixel_str[index++] = 0x000000;
			else
				visual->pixel_str[index++] =
					visual->far_str[(visual->h_far * i) + j];
		}
		index += visual->width - visual->size;
	}
}

void	draw_map(t_map *map, t_visual *visual)
{
	int index;
	int y;
	int x;

	index = 0;
	y = -1;
	while (++y < visual->height / visual->size)
	{
		x = -1;
		while (++x < visual->width / visual->size)
		{
			if (map->map[y][x] == map->player)
				draw_shrek(visual, index);
			else if (map->map[y][x] == map->opponent)
				draw_farquaad(visual, index);
			else
				drawsquare(visual, index, 0xFFFFFF);
			index += visual->size;
		}
		index += visual->width * (visual->size - 1);
	}
	mlx_put_image_to_window(visual->mlx, visual->win,
			visual->img, 0, 0);
}
