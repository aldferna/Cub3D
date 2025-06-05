/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:57:52 by aldferna          #+#    #+#             */
/*   Updated: 2025/06/05 13:23:09 by lumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_new_width(char *line, int *max_width, int *height)
{
	if (get_width(line) > (*max_width))
		(*max_width) = get_width(line);
	(*height)++;
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
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!(ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
				|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ",
					3) == 0 || ft_strncmp(line, "F ", 2) == 0
				|| ft_strncmp(line, "C ", 2) == 0) && (line[0] != '\n'))
		{
			set_new_width(line, &max_width, &height);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map->width = max_width;
	map->height = height;
}

int	manage_end_of_line(t_map *map, int i, int *j)
{
	if (map->map[i][(*j)] == '\n' || map->map[i][(*j)] == '\0')
	{
		if ((*j) > 0 && (map->map[i][(*j) - 1] == 'N'
			|| map->map[i][(*j) - 1] == 'S'
			|| map->map[i][(*j) - 1] == 'W'
			|| map->map[i][(*j) - 1] == 'E'))
		{
			ft_putstr_fd("Error: Map is not surrounded by walls\n", 2);
			exit(2);
		}
		while (((*j) > 0) && ((*j) < map->width))
		{
			map->map[i][(*j)] = map->map[i][(*j) - 1];
			(*j)++;
		}
		return (1);
	}
	return (0);
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
			if (manage_end_of_line(map, i, &j))
				break ;
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
