/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:14:32 by aldferna          #+#    #+#             */
/*   Updated: 2025/05/09 18:49:58 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while(i < map->height)
	{
		printf("%d: %s", i, map->map[i]);
		i++;
	}
	printf("\n");
}

int	get_width(char *line)
{
	int	width;

	width = 0;
	while (line[width] != '\n' && line[width] != '\0')
		width++;
	return (width);
}

void	set_witdh_height(t_map *map)
{
	char	*line;
	int		fd;
	int		height;
	int		max_width;

	max_width = 0;
	height = 0;
	fd = open(map->path, O_RDONLY);
	printf("\n\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line1: %s", line);
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ",
				3) == 0 || ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line,
				"C ", 2) == 0)
			continue ;
		if (line[0] != '\n')
		{
			if (get_width(line) > max_width)
			{
				max_width = get_width(line);
			}
			height++;
		}
		free(line);
	}
	close(fd);
	map->width = max_width;
	map->height = height;
}

void	fill_map(t_map *map)
{
	char	*line;
	int		fd;
	int		i;

	map->map = malloc(sizeof(int *) * map->height);
	if (!map->map)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		return ;
	}
	fd = open(map->path, O_RDONLY);
	i = 0;
	printf("\n\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("L2: %s", line);
		if (line[0] != '\n' && ft_strncmp(line, "NO ", 3) != 0
			&& ft_strncmp(line, "SO ", 3) != 0 && ft_strncmp(line, "WE ",
				3) != 0 && ft_strncmp(line, "EA ", 3) != 0 && ft_strncmp(line,
				"F ", 2) != 0 && ft_strncmp(line, "C ", 2) != 0)
			map->map[i++] = ft_strdup(line);
		free(line);
	}
	close(fd);
}

void	clean_buffer(int fd)
{
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
		free(line);
}

t_map	*init_map(char *map_path)
{
	t_map	*map;
	char	*line;
	int		fd;

	map = malloc(sizeof(t_map));
	if (!map)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		return (NULL);
	}
	map->path = ft_strdup(map_path);
	fd = open(map->path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error: Map doesn't exist");
		exit(2);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("LINE: %s", line);
		if (ft_strncmp(line, "NO ", 3) == 0)
			map->no_texture = ft_strdup(ft_strtrim(line + 3, " \n"));
		else if (ft_strncmp(line, "SO ", 3) == 0)
			map->so_texture = ft_strdup(ft_strtrim(line + 3, " \n"));
		else if (ft_strncmp(line, "WE ", 3) == 0)
			map->we_texture = ft_strdup(ft_strtrim(line + 3, " \n"));
		else if (ft_strncmp(line, "EA ", 3) == 0)
			map->ea_texture = ft_strdup(ft_strtrim(line + 3, " \n"));
		else if (ft_strncmp(line, "F ", 2) == 0)
			map->floor_color = ft_strdup(ft_strtrim(line + 2, " \n"));
		else if (ft_strncmp(line, "C ", 2) == 0)
			map->sky_color = ft_strdup(ft_strtrim(line + 2, " \n"));
		else if (map->sky_color && line[0] != '\n')
			break ;
		free(line);
	}
	free(line);
	clean_buffer(fd);
	close(fd);
	set_witdh_height(map);
	fill_map(map);
	return (map);
}

int	check_name_map(char *str)
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