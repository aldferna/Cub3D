/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_col_tex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:15:24 by aldferna          #+#    #+#             */
/*   Updated: 2025/06/05 12:54:54 by lumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

int	count_commas(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

char	**check_char_split(char *str_color)
{
	int		i;
	char	**rgb;

	i = 0;
	while (str_color[i])
	{
		if (!ft_isdigit(str_color[i]) && str_color[i] != ',')
		{
			ft_putstr_fd("Error: Color values must be ", 2);
			ft_putstr_fd("numbers separated by comas.\n", 2);
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
	return (rgb);
}

int	create_color(char *str_color)
{
	int		i;
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = check_char_split(str_color);
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
	while (rgb[i])
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
	return (r << 24 | g << 16 | b << 8 | 255);
}
