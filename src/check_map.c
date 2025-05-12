/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:41:46 by lumartin          #+#    #+#             */
/*   Updated: 2025/05/12 19:45:02 by lumartin         ###   ########.fr       */
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

static void	free_map_copy(char **map_copy, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

static void	flood_fill(char **map_copy, int x, int y, int height, int width)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return ;
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'F')
		return ;
	map_copy[y][x] = 'F';
	flood_fill(map_copy, x + 1, y, height, width);
	flood_fill(map_copy, x - 1, y, height, width);
	flood_fill(map_copy, x, y + 1, height, width);
	flood_fill(map_copy, x, y - 1, height, width);
}

static int	check_border_openings(t_map *map, char **map_copy)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (map_copy[0][i] != '1')
			return (0);
		if (map_copy[map->height - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map_copy[i][0] != '1')
			return (0);
		if (map_copy[i][map->width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	check_map_enclosed(t_map *map)
{
	char	**map_copy;
	int		is_enclosed;
	int		y;
	int		x;

	map_copy = copy_map(map);
	if (!map_copy)
		return (0);
	is_enclosed = check_border_openings(map, map_copy);
	if (!is_enclosed)
	{
		free_map_copy(map_copy, map->height);
		return (0);
	}
	flood_fill(map_copy, map->player->init_x, map->player->init_y, map->height,
		map->width);
	y = 0;
	while (y < map->height)
	{
		if (map_copy[y][0] == 'F' || map_copy[y][map->width - 1] == 'F')
		{
			free_map_copy(map_copy, map->height);
			return (0);
		}
		y++;
	}
	x = 0;
	while (x < map->width)
	{
		if (map_copy[0][x] == 'F' || map_copy[map->height - 1][x] == 'F')
		{
			free_map_copy(map_copy, map->height);
			return (0);
		}
		x++;
	}
	free_map_copy(map_copy, map->height);
	return (1);
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
			// print_map(&map);
			if (map.map[y][x] && map.map[y][x] != '1' && map.map[y][x] != '0'
				&& map.map[y][x] != 'N' && map.map[y][x] != 'S'
				&& map.map[y][x] != 'E' && map.map[y][x] != 'W'
				&& ft_isspace(map.map[y][x]) == 0)
			{
				ft_putstr_fd("Error: Invalid character in map\n", 2);
				return (0);
			}
			if (map.map[y][x] == 'N' || map.map[y][x] == 'S'
				|| map.map[y][x] == 'E' || map.map[y][x] == 'W')
			{
				if (player == 1)
				{
					ft_putstr_fd("Error: More than one player\n", 2);
					exit(2);
				}
				player = 1;
			}
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

int	check_map(t_map *map)
{
	if (check_char_map(*map) == 0)
		return (0);
	if (is_map_surrounded(map) == 0)
		return (0);
	return (1);
}