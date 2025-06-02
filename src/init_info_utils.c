/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:57:52 by aldferna          #+#    #+#             */
/*   Updated: 2025/06/02 16:58:18 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
