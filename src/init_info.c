/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:14:32 by aldferna          #+#    #+#             */
/*   Updated: 2025/06/11 17:56:44 by lumartin         ###   ########.fr       */
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
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] != '\n' && ft_strncmp(line, "NO", 2) != 0
			&& ft_strncmp(line, "SO", 2) != 0 && ft_strncmp(line, "WE", 2) != 0
			&& ft_strncmp(line, "EA", 2) != 0 && ft_strncmp(line, "F", 1) != 0
			&& ft_strncmp(line, "C", 1) != 0)
			ft_strcpy_fillmap(map, i++, line, (ft_strlen(line) + 1));
		free(line);
		line = get_next_line(fd);
	}
	map->map[i] = NULL;
	close(fd);
	if (!map->map[0])
	{
		free_resources(map);
		ft_putstr_fd("Error: Map is empty\n", 2);
		exit(2);
	}
}

static void	check_extra_info(char *line, int fd, t_map *map)
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
		free_resources(map);
		ft_putstr_fd("Error: Extra information after map\n", 2);
		exit(2);
	}
}

void	read_file_and_fill(int fd, t_map *map)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!map->no_texture && ft_strncmp(line, "NO ", 3) == 0)
			map->no_texture = ft_strtrim(line + 3, " \n");
		else if (!map->so_texture && ft_strncmp(line, "SO ", 3) == 0)
			map->so_texture = ft_strtrim(line + 3, " \n");
		else if (!map->we_texture && ft_strncmp(line, "WE ", 3) == 0)
			map->we_texture = ft_strtrim(line + 3, " \n");
		else if (!map->ea_texture && ft_strncmp(line, "EA ", 3) == 0)
			map->ea_texture = ft_strtrim(line + 3, " \n");
		else if (!map->floor_color && ft_strncmp(line, "F ", 2) == 0)
			map->floor_color = ft_strtrim(line + 2, " \n");
		else if (!map->sky_color && ft_strncmp(line, "C ", 2) == 0)
			map->sky_color = ft_strtrim(line + 2, " \n");
		else if (map->sky_color && map->floor_color && map->no_texture
			&& map->so_texture && map->we_texture && map->ea_texture
			&& line[0] != '\n')
			return (check_extra_info(line, fd, map), clean_buffer(fd));
		free(line);
		line = get_next_line(fd);
	}
	clean_buffer(fd);
}

void	init_player(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < (int)ft_strlen(map->map[y]))
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
	int	fd;

	map->path = ft_strdup(map_path);
	fd = open(map->path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Could not open map file\n", 2);
		free_resources(map);
		exit(2);
	}
	read_file_and_fill(fd, map);
	if (!map->sky_color || !map->floor_color || check_textures(*map) == 1)
	{
		ft_putstr_fd("Error: Missing data or syntax mistake\n", 2);
		free_resources(map);
		exit(2);
	}
	map->f_col = create_color(map->floor_color, map);
	map->s_col = create_color(map->sky_color, map);
	set_witdh_height(map);
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		return (ft_putstr_fd("Error: Memory allocation failed\n", 2), NULL);
	fill_map(map);
	return (replace_spaces(map), map);
}
