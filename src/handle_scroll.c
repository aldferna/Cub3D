/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_scroll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:05:38 by aldferna          #+#    #+#             */
/*   Updated: 2025/06/02 15:12:37 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(game->scroll_speed) - game->dir_y
		* sin(game->scroll_speed);
	game->dir_y = old_dir_x * sin(game->scroll_speed) + game->dir_y
		* cos(game->scroll_speed);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(game->scroll_speed) - game->plane_y
		* sin(game->scroll_speed);
	game->plane_y = old_plane_x * sin(game->scroll_speed) + game->plane_y
		* cos(game->scroll_speed);
}

static void	left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(-game->scroll_speed) - game->dir_y
		* sin(-game->scroll_speed);
	game->dir_y = old_dir_x * sin(-game->scroll_speed) + game->dir_y
		* cos(-game->scroll_speed);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(-game->scroll_speed) - game->plane_y
		* sin(-game->scroll_speed);
	game->plane_y = old_plane_x * sin(-game->scroll_speed) + game->plane_y
		* cos(-game->scroll_speed);
}

void	scroll(double xdelta, double ydelta, void *param)
{
	t_game	*game;

	(void)xdelta;
	game = (t_game *)param;
	if (ydelta > 0)
		left(game);
	else if (ydelta < 0)
		right(game);
}
