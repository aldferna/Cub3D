/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:55:39 by aldara            #+#    #+#             */
/*   Updated: 2025/06/02 14:01:31 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	map_copy = copy_map(map);
	if (!map_copy)
		return (0);
	is_enclosed = check_border_openings(map, map_copy);
	if (!is_enclosed)
	{
		free_map_copy(map_copy, map->height);
		return (0);
	}
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
