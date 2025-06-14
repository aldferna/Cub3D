/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:32:05 by aldara            #+#    #+#             */
/*   Updated: 2025/06/11 18:06:54 by lumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	delete_textures(t_game *game)
{
	mlx_delete_texture(game->north_tex);
	mlx_delete_texture(game->south_tex);
	mlx_delete_texture(game->east_tex);
	mlx_delete_texture(game->west_tex);
	mlx_terminate(game->mlx);
}

void	load_north_south(t_game *game)
{
	game->north_tex = mlx_load_png(game->map->no_texture);
	if (!game->north_tex)
	{
		ft_putstr_fd("Error: Couldn't load north texture\n", 2);
		free_resources(game->map);
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
	game->south_tex = mlx_load_png(game->map->so_texture);
	if (!game->south_tex)
	{
		ft_putstr_fd("Error: Couldn't load south texture\n", 2);
		free_resources(game->map);
		mlx_delete_texture(game->north_tex);
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
}

void	load_textures(t_game *game)
{
	load_north_south(game);
	game->east_tex = mlx_load_png(game->map->ea_texture);
	if (!game->east_tex)
	{
		ft_putstr_fd("Error: Couldn't load east texture\n", 2);
		free_resources(game->map);
		mlx_delete_texture(game->north_tex);
		mlx_delete_texture(game->south_tex);
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
	game->west_tex = mlx_load_png(game->map->we_texture);
	if (!game->west_tex)
	{
		ft_putstr_fd("Error: Couldn't load west texture\n", 2);
		free_resources(game->map);
		mlx_delete_texture(game->north_tex);
		mlx_delete_texture(game->south_tex);
		mlx_delete_texture(game->east_tex);
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
}
