/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:14:32 by aldferna          #+#    #+#             */
/*   Updated: 2025/05/11 22:40:31 by lumartin         ###   ########.fr       */
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
	while (i < map->height)
	{
		printf("%d:	%s\n", i, map->map[i]);
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
	while ((line = get_next_line(fd)) != NULL)
	{
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

	map->map = malloc(sizeof(char *) * map->height);
	if (!map->map)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		return ;
	}
	fd = open(map->path, O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
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

void	replace_spaces(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == '\n')
			{
				while (j < map->width)
				{
					map->map[i][j] = map->map[i][j - 1];
					j++;
				}
				break ;
			}
			else if (map->map[i][j] != '0' && map->map[i][j] != '1'
				&& map->map[i][j] != 'N' && map->map[i][j] != 'S'
				&& map->map[i][j] != 'E' && map->map[i][j] != 'W')
				map->map[i][j] = '1';
			j++;
		}
		map->map[i][j] = '\0';
		i++;
	}
}
t_player	*init_player(t_map *map)
{
	t_player	*player;
	int			x;
	int			y;

	player = malloc(sizeof(t_player));
	if (!player)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		return (NULL);
	}
	x = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S'
				|| map->map[y][x] == 'E' || map->map[y][x] == 'W')
			{
				player->x = x;
				player->y = y;
				player->init_x = x;
				player->init_y = y;
				player->direction = map->map[y][x];
				return (player);
			}
			x++;
		}
		y++;
	}
	return (player);
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
	replace_spaces(map);
	return (map);
}
