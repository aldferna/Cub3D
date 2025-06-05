/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:48:12 by aldferna          #+#    #+#             */
/*   Updated: 2025/06/05 13:24:29 by lumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
/*
void	print_map_copy(char **map_copy)
{
	int	i;

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
*/

void	clean_buffer(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	get_width(char *line)
{
	int	width;

	width = 0;
	while (line[width] != '\n' && line[width] != '\0')
		width++;
	return (width);
}

void	free_map_copy(char **map_copy, int height)
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

void	free_resources(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
	free(map->path);
	free(map->floor_color);
	free(map->sky_color);
	free(map->no_texture);
	free(map->so_texture);
	free(map->we_texture);
	free(map->ea_texture);
	free(map->player);
}

void	ft_strcpy_fillmap(t_map *map, int i, char *str, int lenght)
{
	map->map[i] = malloc(sizeof(char) * lenght);
	if (!map->map[i])
	{
		perror("Error: Map memory alloc failed");
		exit(2);
	}
	ft_strlcpy(map->map[i], str, ft_strlen(str));
}
