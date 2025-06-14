/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:51:59 by lumartin          #+#    #+#             */
/*   Updated: 2025/06/11 18:06:21 by lumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

/**
 * @brief It processes a ray; initilization and trajectory.
 * And draws one wall vertical column.
 */
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

/**
 * @brief Draws the complete frame: first the background,
 * then the walls; column by column.
 */
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

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	render_frame(game);
	handle_keys(game);
	draw_minimap(game);
}

/**
 * @brief Configures thr MLX, loads the textures and initialize the game.
 */
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
		return (ft_putstr_fd("Error: MLX42 initialization\n", 2), 1);
	load_textures(&game);
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.img || (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0))
	{
		ft_putstr_fd("Error: Failed to create image\n", 2);
		delete_textures(&game);
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	delete_textures(&game);
	return (EXIT_SUCCESS);
}
