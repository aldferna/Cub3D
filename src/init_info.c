/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldara <aldara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:14:32 by aldferna          #+#    #+#             */
/*   Updated: 2025/06/03 14:23:54 by aldara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	fill_map(t_map *map)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(map->path, O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] != '\n' && ft_strncmp(line, "NO ", 3) != 0
			&& ft_strncmp(line, "SO ", 3) != 0 && ft_strncmp(line, "WE ",
				3) != 0 && ft_strncmp(line, "EA ", 3) != 0 && ft_strncmp(line,
				"F ", 2) != 0 && ft_strncmp(line, "C ", 2) != 0)
		{
			ft_strcpy_fillmap(map, i, line, (map->width + 1));
			i++;
		}
		free(line);
	}
	map->map[i] = NULL;
	close(fd);
	if (!map->map[0])
	{
		printf("Error: Missing map data\n");
		exit(2);
	}
}

void	check_extra_info(char *line, int fd)
{
	while (line && line[0] != '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line)
	{
		free(line);
		printf("Error: Data after map\n");
		exit(2);
	}
}

void	read_file_and_fill(int fd, t_map *map)
{
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_strncmp(line, "NO ", 3) == 0)
			map->no_texture = ft_strtrim(line + 3, " \n");
		else if (ft_strncmp(line, "SO ", 3) == 0)
			map->so_texture = ft_strtrim(line + 3, " \n");
		else if (ft_strncmp(line, "WE ", 3) == 0)
			map->we_texture = ft_strtrim(line + 3, " \n");
		else if (ft_strncmp(line, "EA ", 3) == 0)
			map->ea_texture = ft_strtrim(line + 3, " \n");
		else if (ft_strncmp(line, "F ", 2) == 0)
			map->floor_color = ft_strtrim(line + 2, " \n");
		else if (ft_strncmp(line, "C ", 2) == 0)
			map->sky_color = ft_strtrim(line + 2, " \n");
		else if (map->sky_color && line[0] != '\n')
		{
			check_extra_info(line, fd);
			break ;
		}
		free(line);
	}
	clean_buffer(fd);
	close(fd);
}

void init_player(t_map *map)
{
	int			x;
	int			y;

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
				map->player->init_x = x;
				map->player->init_y = y;
				map->player->direction = map->map[y][x];
				return ;
			}
			x++;
		}
		y++;
	}
}

t_map	*init_map(char *map_path, t_map *map)
{
	int		fd;

	map->path = ft_strdup(map_path);
	fd = open(map->path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error: Map doesn't exist");
		exit(2);
	}
	read_file_and_fill(fd, map);
	if (!map->sky_color || !map->sky_color[0] || !map->floor_color
		|| !map->floor_color[0] || check_textures(*map) == 1)
	{
		ft_putstr_fd("Error: Missing data or syntax mistake\n", 2);
		exit(2);
	}
	map->f_col = create_color(map->floor_color);
	map->s_col = create_color(map->sky_color);
	set_witdh_height(map);
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
	return (ft_putstr_fd("Error: Memory allocation failed\n", 2), NULL);
	fill_map(map);
	replace_spaces(map);
	return (map);
}
