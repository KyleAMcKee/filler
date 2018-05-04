/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmckee <kmckee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 22:42:33 by kmckee            #+#    #+#             */
/*   Updated: 2018/03/22 23:28:22 by kmckee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	put_piece(int y, int x)
{
	ft_putnbr(y);
	ft_putchar(' ');
	ft_putnbr(x);
	ft_putchar('\n');
}

void	heat_init(t_map *map)
{
	int i;

	i = 0;
	map->heat_map = (int**)malloc(sizeof(int*) * map->height + 1);
	map->heat_map[map->height] = 0;
	while (i < map->height)
	{
		map->heat_map[i] = (int*)malloc(sizeof(int) * map->width);
		i++;
	}
}

void	gfx_map_init(t_visual *visual, t_map *map)
{
	if (map->height == 24)
		visual->size = 40;
	else if (map->height == 15)
		visual->size = 75;
	else
		visual->size = 12;
	visual->height = map->height * visual->size;
	visual->width = map->width * visual->size;
	visual->mlx = mlx_init();
	visual->win = mlx_new_window(visual->mlx, visual->width,
		visual->height, "Filler");
}

void	free_everything(t_map *map)
{
	int i;

	i = -1;
	while (map->piece[++i])
		free(map->piece[i]);
	free(map->piece);
	i = -1;
	while (map->map[++i])
		free(map->map[i]);
	free(map->map);
	i = -1;
	while (map->heat_map[++i])
		free(map->heat_map[i]);
	free(map->heat_map);
	i = -1;
	while (map->new_piece[++i])
		free(map->new_piece[i]);
	free(map->new_piece);
}
