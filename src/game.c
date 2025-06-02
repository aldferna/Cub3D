/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:51:59 by lumartin          #+#    #+#             */
/*   Updated: 2025/06/02 14:43:56 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	else if (game->map->player->direction == 'E')
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
	// if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
	// 		&& ray->ray_dir_y < 0))
	// 	ray->tex_x = tex->width - ray->tex_x - 1;
}

// Coordina los cálculos de altura de pared y texturas
void	calc_wall_height_and_texture(t_game *game, t_ray *ray)
{
	calc_distance_and_height(ray);
	calc_wall_x(game, ray);
	set_texture_direction(ray);
	calc_texture_column(game, ray);
}

// Dibuja una línea vertical de la pared en la coordenada X, aplicando la textura correspondiente
void	draw_wall_line(t_game *game, t_ray *ray, int x)
{
	int				y;
	mlx_texture_t	*tex;
	double			step_scale;
	double			tex_pos;
	int				tex_y;
	uint32_t		*pixels;
	uint32_t		color;
	int				r;
	int				g;
	int				b;

	if (ray->tex_dir == 0)
		tex = game->north_tex;
	else if (ray->tex_dir == 1)
		tex = game->south_tex;
	else if (ray->tex_dir == 2)
		tex = game->east_tex;
	else
		tex = game->west_tex;
	step_scale = (double)tex->height / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* step_scale;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos % tex->height;
		tex_pos += step_scale;
		pixels = (uint32_t *)tex->pixels;
		color = pixels[tex->width * tex_y + ray->tex_x];
		r = (color >> 16) & 0xFF;
		g = (color >> 8) & 0xFF;
		b = color & 0xFF;
		color = (b << 24) | (g << 16) | (r << 8) | 255;
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}

// Procesa completamente un rayo: inicializa, sigue trayectoria y dibuja la línea vertical
void	render_ray_draw_line(t_game *game, int x)
{
	t_ray	ray;

	init_ray(game, &ray, x);
	calc_step_and_side_dist(game, &ray);
	perform_dda(game, &ray);
	draw_mini_ray(game, ray);
	calc_wall_height_and_texture(game, &ray);
	draw_wall_line(game, &ray, x);
}

// Dibuja el cielo y el suelo con los colores definidos en el mapa
void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, game->map->s_col);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, game->map->f_col);
			x++;
		}
		y++;
	}
}

// Dibuja un frame completo: primero el fondo y luego cada columna de píxeles con rayos
void	render_frame(void *param)
{
	t_game	*game;
	int		x;

	game = (t_game *)param;
	draw_background(game);
	x = 0;
	while (x < WIDTH)
	{
		render_ray_draw_line(game, x);
		x++;
	}
}

// Carga las cuatro texturas (norte, sur, este, oeste) desde archivos PNG
void	load_textures(t_game *game)
{
	game->north_tex = mlx_load_png(game->map->no_texture);
	if (!game->north_tex)
	{
		ft_putstr_fd("Error: Couldn't load north texture\n", 2);
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
	game->south_tex = mlx_load_png(game->map->so_texture);
	if (!game->south_tex)
	{
		ft_putstr_fd("Error: Couldn't load south texture\n", 2);
		mlx_delete_texture(game->north_tex);
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
	game->east_tex = mlx_load_png(game->map->ea_texture);
	if (!game->east_tex)
	{
		ft_putstr_fd("Error: Couldn't load east texture\n", 2);
		mlx_delete_texture(game->north_tex);
		mlx_delete_texture(game->south_tex);
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
	game->west_tex = mlx_load_png(game->map->we_texture);
	if (!game->west_tex)
	{
		ft_putstr_fd("Error: Couldn't load west texture\n", 2);
		mlx_delete_texture(game->north_tex);
		mlx_delete_texture(game->south_tex);
		mlx_delete_texture(game->east_tex);
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
}

void	handle_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_resources(game->map);
	free(game->map);
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_keys(game);
	render_frame(game);
	draw_minimap(game);
}

// Inicializa el juego, configura MLX42, carga texturas y ejecuta el bucle principal
int	start_game(t_map *map)
{
	t_game	game;

	game.map = map;
	game.pos_x = map->player->init_x + 0.5;
	game.pos_y = map->player->init_y + 0.5;
	game.move_speed = 0.05;
	game.rot_speed = 0.03;
	game.scroll_speed = 0.1;
	init_direction(&game);
	game.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game.mlx)
	{
		ft_putstr_fd("Error: Failed to initialize MLX42\n", 2);
		return (EXIT_FAILURE);
	}
	load_textures(&game);
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.img || (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0))
	{
		ft_putstr_fd("Error: Failed to create image\n", 2);
		mlx_delete_texture(game.north_tex);
		mlx_delete_texture(game.south_tex);
		mlx_delete_texture(game.east_tex);
		mlx_delete_texture(game.west_tex);
		mlx_terminate(game.mlx);
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_close_hook(game.mlx, handle_close, &game);
	mlx_loop(game.mlx);
	mlx_delete_texture(game.north_tex);
	mlx_delete_texture(game.south_tex);
	mlx_delete_texture(game.east_tex);
	mlx_delete_texture(game.west_tex);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
