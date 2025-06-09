/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:21:49 by aldferna          #+#    #+#             */
/*   Updated: 2025/06/09 20:34:06 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	checker(char c, int *player)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(*player)++;
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& ft_isspace(c) == 0)
	{
		ft_putstr_fd("Error: Invalid character in map\n", 2);
		return (0);
	}
	return (1);
}

static int	check_char_map(t_map map)
{
	int	x;
	int	y;
	int	player;

	player = 0;
	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(map.map[y]))
		{
			if (!checker(map.map[y][x], &player))
				return (0);
			x++;
		}
		y++;
	}
	if (player < 1)
		return (ft_putstr_fd("Error: No player\n", 2), 0);
	else if (player > 1)
		return (ft_putstr_fd("Error: More than one player\n", 2), 0);
	return (1);
}

int	check_map(t_map *map)
{
	if (check_char_map(*map) == 0)
		return (0);
	if (is_map_surrounded(map) == 0)
		return (0);
	return (1);
}
