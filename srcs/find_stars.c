/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_stars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmckee <kmckee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:59:15 by kmckee            #+#    #+#             */
/*   Updated: 2018/03/22 21:19:32 by kmckee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	find_first_star(t_map *map)
{
	int y;
	int x;

	y = 0;
	while (y < map->h_piece)
	{
		x = 0;
		while (x < map->w_piece)
		{
			if (map->piece[y][x] == '*')
			{
				map->x_offset = x;
				map->y_offset = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	get_offset(t_map *map)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (y < map->h_piece)
	{
		while (x < map->w_piece)
		{
			if (map->piece[y][x] == '*')
			{
				if (x < map->x_offset)
				{
					map->x_offset = x;
				}
				if (y < map->y_offset)
					map->y_offset = y;
			}
			x++;
		}
		y++;
		x = 0;
	}
}
