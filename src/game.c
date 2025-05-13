/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:51:59 by lumartin          #+#    #+#             */
/*   Updated: 2025/05/12 21:55:51 by lumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Inicializa los vectores de dirección y plano de la cámara según la orientación inicial del jugador (N,S, E, W)
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

// Maneja el movimiento hacia adelante (tecla W), con detección de colisiones con paredes
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

// Maneja el movimiento hacia atrás (tecla S), con detección de colisiones con paredes
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

// Maneja la rotación a la izquierda (tecla A) mediante transformación de vectores
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

// Maneja la rotación a la derecha (tecla D) mediante transformación de vectores
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

// Maneja la tecla ESC para cerrar la ventana del juego
void	handle_key_esc(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

// Función principal que coordina el manejo de todas las teclas
void	handle_movement(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_key_w(game);
	handle_key_s(game);
	handle_key_a(game);
	handle_key_d(game);
	handle_key_esc(game);
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

// Inicializa los parámetros de un rayo para cada columna de píxeles
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

// Calcula la distancia perpendicular a la pared y la altura de la línea vertical
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
void	calc_wall_x(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

// Determina qué textura usar (norte, sur, este, oeste) según la orientación de la pared
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

// Calcula la coordenada X específica dentro de la textura
void	calc_texture_x(t_game *game, t_ray *ray)
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
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		ray->tex_x = tex->width - ray->tex_x - 1;
}

// Coordina los cálculos de altura de pared y texturas
void	calc_wall_height(t_game *game, t_ray *ray)
{
	calc_distance_and_height(ray);
	calc_wall_x(game, ray);
	set_texture_direction(ray);
	calc_texture_x(game, ray);
}

// Dibuja una línea vertical de la pared en la coordenada X, aplicando la textura correspondiente
void	draw_wall_line(t_game *game, t_ray *ray, int x)
{
	int				y;
	mlx_texture_t	*tex;
	double			step;
	double			tex_pos;
	int				tex_y;
	uint32_t		*pixels;
	uint32_t		color;

	if (ray->tex_dir == 0)
		tex = game->north_tex;
	else if (ray->tex_dir == 1)
		tex = game->south_tex;
	else if (ray->tex_dir == 2)
		tex = game->east_tex;
	else
		tex = game->west_tex;
	step = (double)tex->height / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		pixels = (uint32_t *)tex->pixels;
		color = pixels[tex->width * tex_y + ray->tex_x];
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}

// Procesa completamente un rayo: inicializa, calcula trayectoria y dibuja la línea vertical
void	render_ray(t_game *game, int x)
{
	t_ray	ray;

	init_ray(game, &ray, x);
	calc_step_and_side_dist(game, &ray);
	perform_dda(game, &ray);
	calc_wall_height(game, &ray);
	draw_wall_line(game, &ray, x);
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
		render_ray(game, x);
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

// Inicializa el juego, configura MLX42, carga texturas y ejecuta el bucle principal
int	start_game(t_map *map)
{
	t_game	game;

	game.map = map;
	game.pos_x = map->player->init_x + 0.5;
	game.pos_y = map->player->init_y + 0.5;
	game.move_speed = 0.05;
	game.rot_speed = 0.03;
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
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop_hook(game.mlx, handle_movement, &game);
	mlx_loop(game.mlx);
	mlx_delete_texture(game.north_tex);
	mlx_delete_texture(game.south_tex);
	mlx_delete_texture(game.east_tex);
	mlx_delete_texture(game.west_tex);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
