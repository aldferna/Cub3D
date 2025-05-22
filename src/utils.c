/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:48:12 by aldferna          #+#    #+#             */
/*   Updated: 2025/05/22 18:51:51 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void print_map_copy(char **map_copy)
{
	int i;

	i = 0;
	while (map_copy[i])
	{
		printf("%s\n", map_copy[i]);
		i++;
	}
}

void	print_map(t_map *map)
{
	int	i;

	printf("\nWidth: %d\n", map->width);
	printf("Height: %d\n", map->height);
	printf("Path: %s\n", map->path);
	printf("Floor Color: %s\n", map->floor_color);
	printf("Sky Color: %s\n", map->sky_color);
	printf("NO Texture: %s\n", map->no_texture);
	printf("SO Texture: %s\n", map->so_texture);
	printf("WE Texture: %s\n", map->we_texture);
	printf("EA Texture: %s\n", map->ea_texture);
	printf("Map:\n");
	i = 0;
	while (i < map->height)
	{
		printf("%d:	%s\n", i, map->map[i]);
		i++;
	}
	printf("\n");
}

void	clean_buffer(int fd)
{
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
		free(line);
}
