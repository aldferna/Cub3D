/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:59 by lumartin          #+#    #+#             */
/*   Updated: 2025/05/09 20:05:13 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map(t_map map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.map[y][x] != '1' && map.map[y][x] != '0'
				&& map.map[y][x] != 'N' && map.map[y][x] != 'S'
				&& map.map[y][x] != 'E' && map.map[y][x] != 'W'
				&& ft_isspace(map.map[y][x]) == 0)
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

int check_walls(t_map map)
{
	
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2 || check_name_map(argv[1]))
	{
		ft_putstr_fd("Error: Usage: ./cub3d <map.cub>\n", 2);
		return (1);
	}
	map = init_map(argv[1]);
	if (check_map(*map) == 1 || check_walls(*map) == 1)
		return (0);
	print_map(map);
	return (0);
}
