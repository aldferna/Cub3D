/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_line_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldara <aldara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:00:37 by aldara            #+#    #+#             */
/*   Updated: 2025/06/03 15:01:02 by aldara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Calcula la distancia perpendicular a la pared y la altura de la línea vertical
// Marca el punto inicial y final para pintar
void	calc_distance_and_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

// Calcula el punto exacto donde el rayo golpea la pared
// para saber q parte de la textura aplicar a esa columna
void	calc_wall_x(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

// Determina qué textura usar (norte, sur, este, oeste) según donde impactó y vector de dirección
void	set_texture_direction(t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_dir = 2;
	else if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->tex_dir = 3;
	else if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->tex_dir = 1;
	else
		ray->tex_dir = 0;
}

// Calcula que columan de la textura usar
void	calc_texture_column(t_game *game, t_ray *ray)
{
	mlx_texture_t	*tex;

	if (ray->tex_dir == 0)
		tex = game->north_tex;
	else if (ray->tex_dir == 1)
		tex = game->south_tex;
	else if (ray->tex_dir == 2)
		tex = game->east_tex;
	else
		tex = game->west_tex;
	ray->tex_x = (int)(ray->wall_x * tex->width);
}

// Coordina los cálculos de altura de pared y texturas
void	calc_wall_height_and_texture(t_game *game, t_ray *ray)
{
	calc_distance_and_height(ray);
	calc_wall_x(game, ray);
	set_texture_direction(ray);
	calc_texture_column(game, ray);
}
