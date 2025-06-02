/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:41:46 by lumartin          #+#    #+#             */
/*   Updated: 2025/06/02 14:01:39 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	checker(t_map map, int x, int y, int *player)
{
	if (map.map[y][x] && map.map[y][x] != '1' && map.map[y][x] != '0'
		&& map.map[y][x] != 'N' && map.map[y][x] != 'S' && map.map[y][x] != 'E'
		&& map.map[y][x] != 'W' && ft_isspace(map.map[y][x]) == 0)
	{
		ft_putstr_fd("Error: Invalid character in map\n", 2);
		exit(2);
	}
	if (map.map[y][x] == 'N' || map.map[y][x] == 'S' || map.map[y][x] == 'E'
		|| map.map[y][x] == 'W')
	{
		if ((*player) == 1)
		{
			ft_putstr_fd("Error: More than one player\n", 2);
			exit(2);
		}
		(*player) = 1;
	}
	return (*player);
}

static int	check_char_map(t_map map)
{
	int	x;
	int	y;
	int	player;

	y = 0;
	player = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			checker(map, x, y, &player);
			x++;
		}
		y++;
	}
	if (player == 0)
	{
		ft_putstr_fd("Error: No players\n", 2);
		exit(2);
	}
	return (1);
}

int	check_map(t_map *map)
{
	if (check_char_map(*map) == 0)
		return (0);
	if (is_map_surrounded(map) == 0)
		return (0);
	return (1);
}
