/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:59 by lumartin          #+#    #+#             */
/*   Updated: 2025/06/11 17:50:12 by lumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	check_name_map(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 5)
		return (1);
	if (str[len - 4] != '.' || str[len - 3] != 'c' || str[len - 2] != 'u'
		|| str[len - 1] != 'b')
		return (1);
	return (0);
}

static void	init_tmap(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->path = NULL;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor_color = NULL;
	map->sky_color = NULL;
	map->map = NULL;
	map->player = NULL;
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2 || check_name_map(argv[1]))
	{
		ft_putstr_fd("Error: Usage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	map = malloc(sizeof(t_map));
	init_tmap(map);
	if (!map)
		return (ft_putstr_fd("Error: Map memory allocation failed\n", 2), 1);
	init_map(argv[1], map);
	map->player = malloc(sizeof(t_player));
	if (!map->player)
		return (ft_putstr_fd("Error: Player memory allocation failed\n", 2), 1);
	init_player(map);
	if (check_map(map) == 0)
	{
		ft_putstr_fd("Error: Invalid map\n", 2);
		return (free_resources(map), 1);
	}
	start_game(map);
	return (free_resources(map), 0);
}
