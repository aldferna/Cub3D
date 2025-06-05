/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:40:05 by aldara            #+#    #+#             */
/*   Updated: 2025/06/05 12:57:23 by lumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_west_east(t_game *game)
{
	if (game->map->player->direction == 'E')
	{
		game->dir_x = 1.0;
		game->dir_y = 0.0;
		game->plane_x = 0.0;
		game->plane_y = 0.66;
	}
	else if (game->map->player->direction == 'W')
	{
		game->dir_x = -1.0;
		game->dir_y = 0.0;
		game->plane_x = 0.0;
		game->plane_y = -0.66;
	}
}

/**
 * @brief Initializes the direction vectors (and the perpendicular)
 * depending on player orientation.
 */
void	init_direction(t_game *game)
{
	if (game->map->player->direction == 'N')
	{
		game->dir_x = 0.0;
		game->dir_y = -1.0;
		game->plane_x = 0.66;
		game->plane_y = 0.0;
	}
	else if (game->map->player->direction == 'S')
	{
		game->dir_x = 0.0;
		game->dir_y = 1.0;
		game->plane_x = -0.66;
		game->plane_y = 0.0;
	}
	init_west_east(game);
}

/**
 * @brief 1. Calculates the direction vector of the new ray.
 * 2. Sets the player coordenates.
 * 3. Calculates distance vector-> distance to reach X/Y line
 * in an specific direction.
 *
 * camera_x => deviation proportion / angulation according to the pixel in X.
 */
void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2.0 * x / (double)WIDTH - 1.0;
	ray->ray_dir_x = game->dir_x + game->plane_x * ray->camera_x;
	ray->ray_dir_y = game->dir_y + game->plane_y * ray->camera_x;
	ray->map_x = (int)game->pos_x;
	ray->map_y = (int)game->pos_y;
	ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	ray->hit = 0;
}

/**
 * @brief Calculates the step direction and initial side distances
 * for DDA raycasting.
 *
 * step => The direction for x/y movement in the map grid.
 * side_dist_x or y => The initial side distances from the player's
 * position to the first potential grid boundary along the ray's path.
 */
void	calc_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->pos_y) * ray->delta_dist_y;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y >= 0 && ray->map_y < game->map->height && ray->map_x >= 0
			&& ray->map_x < game->map->width)
		{
			if (game->map->map[ray->map_y][ray->map_x] == '1')
				ray->hit = 1;
		}
		else
			break ;
	}
}
