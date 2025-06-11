/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:43:24 by aldara            #+#    #+#             */
/*   Updated: 2025/06/11 18:09:49 by lumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	handle_key_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
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

void	handle_key_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
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
