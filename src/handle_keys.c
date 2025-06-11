/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:43:24 by aldara            #+#    #+#             */
/*   Updated: 2025/06/11 23:19:19 by lumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	handle_key_w(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		if (game->map->map[(int)(game->pos_y)][(int)(game->pos_x + game->dir_x
				* game->move_speed)] != '1')
			game->pos_x += game->dir_x * game->move_speed;
		if (game->map->map[(int)(game->pos_y + game->dir_y
				* game->move_speed)][(int)(game->pos_x)] != '1')
			game->pos_y += game->dir_y * game->move_speed;
	}
}

void	handle_key_s(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		if (game->map->map[(int)(game->pos_y)][(int)(game->pos_x - game->dir_x
				* game->move_speed)] != '1')
			game->pos_x -= game->dir_x * game->move_speed;
		if (game->map->map[(int)(game->pos_y - game->dir_y
				* game->move_speed)][(int)(game->pos_x)] != '1')
			game->pos_y -= game->dir_y * game->move_speed;
	}
}

void	handle_key_a(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		if (game->map->map[(int)(game->pos_y)][(int)(game->pos_x + game->dir_y
				* game->move_speed)] != '1')
			game->pos_x += game->dir_y * game->move_speed;
		if (game->map->map[(int)(game->pos_y - game->dir_x
				* game->move_speed)][(int)(game->pos_x)] != '1')
			game->pos_y -= game->dir_x * game->move_speed;
	}
}

void	handle_key_d(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		if (game->map->map[(int)(game->pos_y)][(int)(game->pos_x - game->dir_y
				* game->move_speed)] != '1')
			game->pos_x -= game->dir_y * game->move_speed;
		if (game->map->map[(int)(game->pos_y + game->dir_x
				* game->move_speed)][(int)(game->pos_x)] != '1')
			game->pos_y += game->dir_x * game->move_speed;
	}
}

void	handle_keys(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_key_w(game);
	handle_key_s(game);
	handle_key_a(game);
	handle_key_d(game);
	handle_key_left(game);
	handle_key_right(game);
	mlx_scroll_hook(game->mlx, &scroll, game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		free_resources(game->map);
		mlx_close_window(game->mlx);
		exit(2);
	}
}
