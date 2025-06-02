/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:59 by lumartin          #+#    #+#             */
/*   Updated: 2025/06/02 17:44:36 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	t_map	*map;

	if (argc != 2 || check_name_map(argv[1]))
	{
		ft_putstr_fd("Error: Usage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	map = malloc(sizeof(t_map));
	if (!map)
		return(ft_putstr_fd("Error: Map memory allocation failed\n", 2), 1);
	init_map(argv[1], map);
	map->player = malloc(sizeof(t_player));
	if (!map->player)
		return (ft_putstr_fd("Error: Player memory allocation failed\n", 2), 1);
	init_player(map);
	if (check_map(map) == 0)
	{
		ft_putstr_fd("Error: Invalid map\n", 2);
		free_resources(map);
		free(map);
		return (1);
	}
	start_game(map);
	return (0);
}
