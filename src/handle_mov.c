/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldara <aldara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:43:24 by aldara            #+#    #+#             */
/*   Updated: 2025/06/01 20:36:00 by aldara           ###   ########.fr       */
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
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		old_dir_x = game->dir_x;
		game->dir_x = game->dir_x * cos(-game->rot_speed) - game->dir_y
			* sin(-game->rot_speed);
		game->dir_y = old_dir_x * sin(-game->rot_speed) + game->dir_y
			* cos(-game->rot_speed);
		old_plane_x = game->plane_x;
		game->plane_x = game->plane_x * cos(-game->rot_speed) - game->plane_y
			* sin(-game->rot_speed);
		game->plane_y = old_plane_x * sin(-game->rot_speed) + game->plane_y
			* cos(-game->rot_speed);
	}
}

void	handle_key_d(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		old_dir_x = game->dir_x;
		game->dir_x = game->dir_x * cos(game->rot_speed) - game->dir_y
			* sin(game->rot_speed);
		game->dir_y = old_dir_x * sin(game->rot_speed) + game->dir_y
			* cos(game->rot_speed);
		old_plane_x = game->plane_x;
		game->plane_x = game->plane_x * cos(game->rot_speed) - game->plane_y
			* sin(game->rot_speed);
		game->plane_y = old_plane_x * sin(game->rot_speed) + game->plane_y
			* cos(game->rot_speed);
	}
}

void	handle_movement(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_key_w(game);
	handle_key_s(game);
	handle_key_a(game);
	handle_key_d(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		free_resources(game->map);
		free(game->map);
		mlx_close_window(game->mlx);
		exit(2);
	}
}
