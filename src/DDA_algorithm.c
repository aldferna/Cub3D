/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldara <aldara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:40:05 by aldara            #+#    #+#             */
/*   Updated: 2025/06/03 14:58:33 by aldara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void init_west_east(t_game *game)
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

// Inicializa los vectores de dirección
// y plano de la cámara según la orientación inicial del jugador (N,S, E, W)
void	init_direction(t_game *game)
{
	if (game->map->player->direction == 'N')
	{
		game->dir_x = 0.0; // vector de direccion -> (0, -1) = norte
		game->dir_y = -1.0;
		game->plane_x = 0.66; // vector perpendicular
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

// Inicializa los parámetros de un rayo para cada columna de píxeles
// calcula el vector de direccion del nuevo rayo
// coordenada del personaje
// calcula vector de distancia-> cuanto se debe mover para avanzar en X/Y en dir concreta
void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2.0 * x / (double)WIDTH - 1.0;               
		// proporcio de desvio/angulacion segun pixel en X
	ray->ray_dir_x = game->dir_x + game->plane_x * ray->camera_x;
		// delta x vector dir nuevo rayo
	ray->ray_dir_y = game->dir_y + game->plane_y * ray->camera_x;
		//(vector central + desviacion)
	ray->map_x = (int)game->pos_x;
	ray->map_y = (int)game->pos_y;
	ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x); // delta x vector distancia
	ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	ray->hit = 0;
}

// Calcula la dirección de paso del rayo y las distancias iniciales
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

// Ejecuta el algoritmo DDA para encontrar qué pared golpea el rayo
void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // cruza linea vertical
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
