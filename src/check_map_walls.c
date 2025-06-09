/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:41:46 by lumartin          #+#    #+#             */
/*   Updated: 2025/06/09 20:27:18 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	**copy_map(t_map *map)
{
	char	**copy;
	int		i;

	copy = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy[i] = ft_strdup(map->map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	flood_fill(char **map_copy, int x, int y, t_map map)
{
	if (x < 0 || y < 0 || x >= map.width || y >= map.height)
		return ;
	if ((int)ft_strlen(map_copy[y]) - 1 < x)
	{
		map_copy[0][0] = 'A';
		return ;
	}
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'F')
		return ;
	map_copy[y][x] = 'F';
	flood_fill(map_copy, x + 1, y, map);
	flood_fill(map_copy, x - 1, y, map);
	flood_fill(map_copy, x, y + 1, map);
	flood_fill(map_copy, x, y - 1, map);
}

static int	check_border_openings(t_map *map)
{
	int	x;

	x = 0;
	while (x < (int)ft_strlen(map->map[0]) - 1)
	{
		if (map->map[0][x] == 'F')
			return (0);
		x++;
	}
	x = 0;
	while (x < (int)ft_strlen(map->map[map->height - 1]) - 1)
	{
		if (map->map[map->height - 1][x] == 'F')
			return (0);
		x++;
	}
	x = 0;
	while (x < map->height)
	{
		if (map->map[x][0] == 'F')
			return (0);
		x++;
	}
	return (1);
}

static int	check_map_enclosed(t_map *map)
{
	char	**map_copy;
	int		closed;

	closed = 0;
	map_copy = copy_map(map);
	if (!map_copy)
		return (0);
	flood_fill(map_copy, map->player->init_x, map->player->init_y, *map);
	closed = check_border_openings(map);
	if (!closed)
		return (free_map_copy(map_copy, map->height), 0);
	if (map_copy[0][0] == 'A')
		return (free_map_copy(map_copy, map->height), 0);
	free_map_copy(map_copy, map->height);
	return (1);
}

int	is_map_surrounded(t_map *map)
{
	if (!map || !map->map)
		return (0);
	if (check_map_enclosed(map) == 0)
	{
		ft_putstr_fd("Error: Map is not surrounded by walls\n", 2);
		return (0);
	}
	return (1);
}
