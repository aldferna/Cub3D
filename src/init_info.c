/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:14:32 by aldferna          #+#    #+#             */
/*   Updated: 2025/06/02 19:02:06 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
		{
			free(line);
			continue ;
		}
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

	map->map = malloc(sizeof(char *) * (map->height + 1));
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
		{
			map->map[i] = malloc(sizeof(char) * (map->width + 1));
			ft_strlcpy(map->map[i], line, ft_strlen(line));
			i++;
		}
		free(line);
	}
	map->map[i] = NULL;
	close(fd);
	clean_buffer(fd);
	if (!map->map[0])
	{
		printf("Error: Missing map data\n");
		exit(2);
	}
}

// int manage_end_of_line(t_map *map, int i, int *j)
// {
// 	if (map->map[i][(*j)] == '\n' || map->map[i][(*j)] == '\0')
// 	{
// 		if ((*j) > 0 && (map->map[i][(*j) - 1] == 'N' || map->map[i][(*j) - 1] == 'S'
// 			|| map->map[i][(*j) - 1] == 'W' || map->map[i][(*j) - 1] == 'E'))
// 		{
// 			ft_putstr_fd("Error: Map is not surrounded by walls\n", 2);
// 			exit(2);
// 		}
// 		while (((*j) > 0) && ((*j) < map->width))
// 		{
// 			map->map[i][(*j)] = map->map[i][(*j) - 1];
// 			(*j)++;
// 		}
// 	}
// 	return (1);
// }

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
			// if (manage_end_of_line(map, i, &j) == 1)
			// 	break;
			if (map->map[i][j] == '\n' || map->map[i][j] == '\0')
			{
				if (j > 0 && (map->map[i][j - 1] == 'N' || map->map[i][j - 1] == 'S'
					|| map->map[i][j - 1] == 'W' || map->map[i][j - 1] == 'E'))
				{
					ft_putstr_fd("Error: Map is not surrounded by walls\n", 2);
					exit(2);
				}
				while (j > 0 && j < map->width)
				{
					map->map[i][j] = map->map[i][j - 1];
					j++;
				}
				break ;
			}
			else if (map->map[i][j] == '\t')
			{
				ft_putstr_fd("Error: Tabs are not allowed\n", 2);
				exit(2);
			}
			else if (ft_isspace(map->map[i][j]))
				map->map[i][j] = '1';
			j++;
		}
		map->map[i][j] = '\0';
		i++;
	}
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
	fill_map(map);
	replace_spaces(map);
	return (map);
}
