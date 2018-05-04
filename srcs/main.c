/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmckee <kmckee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 11:39:48 by kmckee            #+#    #+#             */
/*   Updated: 2018/03/22 23:26:43 by kmckee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_info(t_map *map)
{
	char *line;

	get_next_line(0, &line);
	map->player = (line[10] == '1' ? 'O' : 'X');
	map->opponent = (line[10] == '1' ? 'X' : 'O');
	free(line);
	get_next_line(0, &line);
	map->height = ft_atoi(&line[8]);
	map->width = ft_atoi(&line[11]);
	free(line);
}

void	get_piece(t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	get_next_line(0, &line);
	map->h_piece = ft_atoi(&line[6]);
	map->w_piece = ft_atoi(&line[8]);
	map->piece = (char**)malloc(sizeof(char*) * map->h_piece + 1);
	map->piece[map->h_piece] = 0;
	free(line);
	while (i < map->h_piece)
	{
		get_next_line(0, &line);
		map->piece[i] = ft_strdup(line);
		free(line);
		i++;
	}
}

void	get_map(t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	map->map = (char**)malloc(sizeof(char*) * (map->height + 1));
	map->map[map->height] = 0;
	get_next_line(0, &line);
	free(line);
	get_next_line(0, &line);
	free(line);
	while (i < map->height)
	{
		get_next_line(0, &line);
		map->map[i] = ft_strdup(&line[4]);
		free(line);
		i++;
	}
	get_piece(map);
	resize_piece(map);
}

void	init_map(t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	get_next_line(0, &line);
	map->map = (char**)malloc(sizeof(char*) * (map->height + 1));
	map->map[map->height] = 0;
	free(line);
	while (i < map->height)
	{
		get_next_line(0, &line);
		map->map[i] = ft_strdup(&line[4]);
		free(line);
		i++;
	}
	get_piece(map);
	resize_piece(map);
}

int		main(void)
{
	t_map		*map;
	t_visual	*visual;

	map = (t_map*)ft_memalloc(sizeof(t_map));
	visual = (t_visual*)ft_memalloc(sizeof(t_visual));
	get_info(map);
	init_map(map);
	heat_init(map);
	heat_convert(map);
	heat_find(map);
	heat_calculate(map);
	gfx_map_init(visual, map);
	shrek_init(visual);
	create_map(visual);
	algorithm(map, visual);
	while (1)
	{
		mlx_do_sync(visual->mlx);
		get_map(map);
		heat_init(map);
		heat_convert(map);
		heat_find(map);
		heat_calculate(map);
		algorithm(map, visual);
	}
}
