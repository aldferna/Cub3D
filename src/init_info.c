/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldara <aldara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:14:32 by aldferna          #+#    #+#             */
/*   Updated: 2025/06/01 20:45:20 by aldara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (!map->map[0]) //|| !map->map[1]) quitas esto se puede quitar
	{
		printf("Error: Missing map data\n");
		exit(2);
	}
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
			if (map->map[i][j] == '\n' || map->map[i][j] == '\0')
			{
				if (map->map[i][j - 1] == 'N' || map->map[i][j - 1] == 'S'
				|| map->map[i][j - 1] == 'W' || map->map[i][j - 1] == 'E')
				{
					ft_putstr_fd("Error: Map is not surrounded by walls\n", 2);
					exit(2);
				}
				while (j < map->width)
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

int count_commas(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return count;
}

int	create_color(char *str_color)
{
	int		i;
	char	**rgb;
	int		r;
	int		g;
	int		b;

	i = 0;
	while (str_color[i])
	{
		if (!ft_isdigit(str_color[i]) && str_color[i] != ',')
		{
			ft_putstr_fd("Error: Color values must be numbers separated by comas (no spaces)\n",
				2);
			exit(2);
		}
		i++;
	}
	rgb = ft_split(str_color, ',');
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3 || count_commas(str_color) > 2)
	{
		ft_putstr_fd("Error: Color syntax: [0,0,0]\n", 2);
		exit(2);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r > 255 || g > 255 || b > 255)
	{
		ft_putstr_fd("Error: RGB channels cannot exceed value 255 (1byte)\n",
			2);
		exit(2);
	}
	i = 0;
	while(rgb[i])
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
	return (r << 24 | g << 16 | b << 8 | 255);
}

int	check_texture(char *str, char *tag)
{
	if (!str || !str[0])
		return (1);
	if (ft_strncmp(str, tag, 2) == 0)
		return (1);
	if ((str[0] != '.' && !ft_isalnum(str[0])))
		return (1);
	return (0);
}

int	check_textures(t_map map)
{
	if (check_texture(map.no_texture, "NO") == 1
		|| check_texture(map.so_texture, "SO") == 1
		|| check_texture(map.we_texture, "WE") == 1
		|| check_texture(map.ea_texture, "EA") == 1)
		return (1);
	return (0);
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
			break ;
		}
		free(line);
	}
	if (!map->sky_color || !map->sky_color[0] || !map->floor_color
		|| !map->floor_color[0] || check_textures(*map) == 1)
	{
		ft_putstr_fd("Error: Missing data or syntax mistake\n", 2);
		exit(2);
	}
	map->f_col = create_color(map->floor_color);
	map->s_col = create_color(map->sky_color);
	free(line);
	clean_buffer(fd);
	close(fd);
	set_witdh_height(map);
	fill_map(map);
	replace_spaces(map);
	return (map);
}
