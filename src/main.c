/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:59 by lumartin          #+#    #+#             */
/*   Updated: 2025/05/12 20:10:14 by lumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_name_map(char *str)
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

int	main(int argc, char **argv)
{
	t_map		*map;
	t_player	*player;

	if (argc != 2 || check_name_map(argv[1]))
	{
		ft_putstr_fd("Error: Usage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	map = init_map(argv[1]);
	player = init_player(map);
	map->player = player;
	if (check_map(map) == 0)
	{
		ft_putstr_fd("Error: Invalid map\n", 2);
		free(map->player);
		free(map);
		return (1);
	}
	start_game(map);
	return (0);
}
