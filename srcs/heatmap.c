/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmckee <kmckee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 20:32:03 by kmckee            #+#    #+#             */
/*   Updated: 2018/03/22 23:05:15 by kmckee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	heat_convert(t_map *map)
{
	int y;
	int x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == '.')
				map->heat_map[y][x] = 0;
			else if (map->map[y][x] == map->player ||
					map->map[y][x] == map->player + 32)
				map->heat_map[y][x] = -1;
			else if (map->map[y][x] == map->opponent ||
					map->map[y][x] == map->opponent + 32)
				map->heat_map[y][x] = -2;
			x++;
		}
		y++;
	}
}

/*
**  Check for all surrounding spaces to see if there is an enemy piece there
**  1 2 3 [y - 1, x - 1] [y - 1, x] [y - 1, x + 1]
**  4 * 5 [y, x - 1] [y, x + 1]
**  6 7 8 [y + 1, x - 1] [y + 1, x] [y + 1, x + 1]
*/

void	heat_populate(t_map *map, int y, int x)
{
	if (x - 1 >= 0 && y - 1 >= 0 && map->heat_map[y - 1][x - 1] == -2)
		map->heat_map[y][x] = 1;
	if (y - 1 >= 0 && map->heat_map[y - 1][x] == -2)
		map->heat_map[y][x] = 1;
	if (y - 1 >= 0 && x + 1 < map->width && map->heat_map[y - 1][x + 1] == -2)
		map->heat_map[y][x] = 1;
	if (x - 1 >= 0 && map->heat_map[y][x - 1] == -2)
		map->heat_map[y][x] = 1;
	if (x + 1 < map->width && map->heat_map[y][x + 1] == -2)
		map->heat_map[y][x] = 1;
	if (y + 1 < map->height && x - 1 >= 0 && map->heat_map[y + 1][x - 1] == -2)
		map->heat_map[y][x] = 1;
	if (y + 1 < map->height && map->heat_map[y + 1][x] == -2)
		map->heat_map[y][x] = 1;
	if (y + 1 < map->height && x + 1 < map->width &&
		map->heat_map[y + 1][x + 1] == -2)
		map->heat_map[y][x] = 1;
}

/*
**  Find any space that contains neither a player's nor an enemy's piece
*/

void	heat_find(t_map *map)
{
	int y;
	int x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->heat_map[y][x] == 0)
				heat_populate(map, y, x);
			x++;
		}
		y++;
	}
}

void	heat_put(t_map *map, int y, int x, int i)
{
	if (x - 1 >= 0 && y - 1 >= 0 && map->heat_map[y - 1][x - 1] == i)
		map->heat_map[y][x] = i + 1;
	if (y - 1 >= 0 && map->heat_map[y - 1][x] == i)
		map->heat_map[y][x] = i + 1;
	if (y - 1 >= 0 && x + 1 < map->width && map->heat_map[y - 1][x + 1] == i)
		map->heat_map[y][x] = i + 1;
	if (x - 1 >= 0 && map->heat_map[y][x - 1] == i)
		map->heat_map[y][x] = i + 1;
	if (x + 1 < map->width && map->heat_map[y][x + 1] == i)
		map->heat_map[y][x] = i + 1;
	if (y + 1 < map->height && x - 1 >= 0 && map->heat_map[y + 1][x - 1] == i)
		map->heat_map[y][x] = i + 1;
	if (y + 1 < map->height && map->heat_map[y + 1][x] == i)
		map->heat_map[y][x] = i + 1;
	if (y + 1 < map->height && x + 1 < map->width &&
		map->heat_map[y + 1][x + 1] == i)
		map->heat_map[y][x] = i + 1;
}

void	heat_calculate(t_map *map)
{
	int y;
	int x;
	int i;

	i = 1;
	while (i < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			x = 0;
			while (x < map->width)
			{
				if (map->heat_map[y][x] == 0)
					heat_put(map, y, x, i);
				x++;
			}
			y++;
		}
		i++;
	}
}
