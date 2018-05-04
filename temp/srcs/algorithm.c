/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmckee <kmckee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 19:54:27 by kmckee            #+#    #+#             */
/*   Updated: 2018/03/22 22:58:02 by kmckee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		piece_in_bounds(t_map *map, int y, int x)
{
	int j;
	int i;

	j = 0;
	while (j <= map->h_piece)
	{
		i = 0;
		while (i <= map->w_piece)
		{
			if ((x + i < 0 && map->new_piece[j][i] == '*') ||
					(y + j < 0 && map->new_piece[j][i] == '*'))
				return (0);
			if ((x + i >= map->width && map->new_piece[j][i] == '*') ||
					(y + j >= map->height && map->new_piece[j][i] == '*'))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

int		get_score(t_map *map, int *y, int *x, int *score)
{
	int i;
	int j;

	j = -1;
	while (++j <= map->h_piece)
	{
		i = -1;
		while (++i <= map->w_piece)
		{
			if (map->heat_map[*y + j][*x + i] == -1 &&
					map->new_piece[j][i] == '*')
				map->star++;
			else if (map->heat_map[*y + j][*x + i] == -2 &&
					map->new_piece[j][i] == '*')
				return (-1);
			else if (map->heat_map[*y + j][*x + i] == 0 &&
					map->new_piece[j][i] == '*')
				*score += 250;
			else
				*score += map->heat_map[*y + j][*x + i];
			if (map->star > 1)
				return (-1);
		}
	}
	return (1);
}

int		is_valid_placement(t_map *map, int y, int x, int *score)
{
	map->star = 0;
	if (piece_in_bounds(map, y, x) == 0)
		return (-1);
	if (get_score(map, &y, &x, score) == -1)
		return (-1);
	if (map->star == 1)
		return (1);
	return (-1);
}

void	check_all_spots(t_map *map, int *score, int y, int x)
{
	int i;
	int j;

	j = -1;
	while (++j <= map->h_piece)
	{
		i = -1;
		while (++i <= map->w_piece)
		{
			if (map->new_piece[j][i] == '*')
			{
				if (is_valid_placement(map, y - j, x - i, score) == 1)
				{
					if (*score < map->score)
					{
						map->score = *score;
						map->x_print = x - i;
						map->y_print = y - j;
						map->valid = 1;
					}
				}
			}
			*score = 0;
		}
	}
}

void	algorithm(t_map *map, t_visual *visual)
{
	int x;
	int y;
	int score;

	y = -1;
	score = 0;
	map->score = 10000;
	map->y_print = 0;
	map->x_print = 0;
	map->valid = 0;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->heat_map[y][x] == -1)
				check_all_spots(map, &score, y, x);
		}
	}
	if (map->valid)
		put_piece(map->y_print - map->y_offset, map->x_print - map->x_offset);
	else
		draw_win(visual);
	draw_map(map, visual);
	free_everything(map);
}
