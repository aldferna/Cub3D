/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldara <aldara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:59 by lumartin          #+#    #+#             */
/*   Updated: 2025/05/11 21:03:31 by aldara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_map(t_map map)
{
	int x;
	int y;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.map[y][x] && map.map[y][x] != '1' && map.map[y][x] != '0' && map.map[y][x] != 'N' && map.map[y][x] != 'S' && map.map[y][x] != 'E' && map.map[y][x] != 'W' && ft_isspace(map.map[y][x]) == 0)
			{
				ft_putstr_fd("Error: Invalid character in map\n", 2);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int check_walls(t_map map_s)
{
	int x;
	int y;

	x = 0;
	while (map_s.map[0][x])
	{
		if (map_s.map[0][x] != '1' && !ft_isspace(map_s.map[0][x]))
			return 1;
		x++;
	}
	x = 0;
	while (map_s.map[map_s.height - 1][x])
	{
		if (map_s.map[map_s.height - 1][x] != '1' && !ft_isspace(map_s.map[map_s.height - 1][x]))
			return 1;
		x++;
	}
	y = 1;
	while (y < (map_s.height - 1))
	{
		x = ft_strlen(map_s.map[y]) - 2;
		if (map_s.map[y][0] && map_s.map[y][x])
		{
			if ((map_s.map[y][0] != '1' && !ft_isspace(map_s.map[y][0])) 
			|| (map_s.map[y][x] != '1' && !ft_isspace(map_s.map[y][x])))
				return 1;
		}
		y++;
	}
	return 0;
}

int main(int argc, char **argv)
{
	t_map *map;

	if (argc != 2 || check_name_map(argv[1]))
	{
		ft_putstr_fd("Error: Usage: ./cub3d <map.cub>\n", 2);
		return (1);
	}
	map = init_map(argv[1]);
	if (check_map(*map) == 1)
		return (1);
	if (check_walls(*map) == 1)
	{
		ft_putstr_fd("Error: Unclosed map\n", 2);
		return (1);	
	}
	print_map(map);
	return (0);
}
