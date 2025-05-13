/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldara <aldara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:43:24 by aldara            #+#    #+#             */
/*   Updated: 2025/05/13 17:45:59 by aldara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
