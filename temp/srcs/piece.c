/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmckee <kmckee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 15:58:12 by kmckee            #+#    #+#             */
/*   Updated: 2018/03/22 21:18:30 by kmckee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	copy_piece(t_map *map)
{
	int i;
	int j;
	int temp;

	j = 0;
	temp = map->min_x;
	while (map->min_y <= map->max_y)
	{
		i = 0;
		while (map->min_x <= map->max_x)
		{
			if (map->piece[map->min_y][map->min_x] == '*')
				map->new_piece[j][i] = '*';
			else
				map->new_piece[j][i] = '.';
			map->min_x++;
			i++;
		}
		map->min_x = temp;
		map->min_y++;
		j++;
	}
}

void	make_piece(t_map *map)
{
	int rows;
	int cols;
	int i;

	rows = map->max_y - map->min_y + 1;
	cols = map->max_x - map->min_x + 1;
	map->new_piece = (char**)malloc(sizeof(char*) * rows + 1);
	map->new_piece[rows] = 0;
	i = 0;
	while (i < rows)
	{
		map->new_piece[i] = (char*)malloc(sizeof(char) * cols + 1);
		map->new_piece[i][cols] = '\0';
		i++;
	}
	get_offset(map);
	map->w_piece = cols - 1;
	map->h_piece = rows - 1;
	copy_piece(map);
}

void	set_min_max(t_map *map, int *i, int *j)
{
	map->stars++;
	if (*j < map->min_y)
		map->min_y = *j;
	if (*i < map->min_x)
		map->min_x = *i;
	if (*j > map->max_y)
		map->max_y = *j;
	if (*i > map->max_x)
		map->max_x = *i;
}

void	resize_piece(t_map *map)
{
	int i;
	int j;

	j = -1;
	find_first_star(map);
	map->min_x = map->x_offset;
	map->min_y = map->y_offset;
	map->max_x = map->x_offset;
	map->max_y = map->y_offset;
	map->stars = 0;
	while (++j < map->h_piece)
	{
		i = -1;
		while (++i < map->w_piece)
		{
			if (map->piece[j][i] == '*')
				set_min_max(map, &i, &j);
		}
	}
	make_piece(map);
}
