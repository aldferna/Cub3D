/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldara <aldara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:57:04 by aldara            #+#    #+#             */
/*   Updated: 2025/06/01 19:11:09 by aldara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_mini_ray(t_game *game, t_ray ray)
{
	int scale;
	int x_y_init[2];
	int x_y_end[2];
	int dx;
	int dy;

    scale = 10;
	while ((game->map->width * scale) > (WIDTH / 4) || (game->map->height * scale) > (HEIGHT / 4))
		scale--;
	x_y_init[0] = game->pos_x * scale;
	x_y_init[1] = game->pos_y * scale;
	x_y_end[0] = ray.map_x * scale;
	x_y_end[1] = ray.map_y * scale;
	dx = x_y_end[0] - x_y_init[0];
	dy = x_y_end[1] - x_y_init[1];
	if (abs(dx) > abs(dy))
		draw_line_h(x_y_init[0], x_y_init[1], x_y_end, game);
	draw_line_v(x_y_init[0], x_y_init[1], x_y_end, game);
}

static int draw_mini_walls(t_game *game, int matrix_x, int matrix_y)
{
	int px;
    int py;
    int init_pixel_x;
    int init_pixel_y;
	int scale;

    scale = 10;
	while ((game->map->width * scale) > (WIDTH / 4) || (game->map->height * scale) > (HEIGHT / 4))
		scale--;
	init_pixel_x = matrix_x * scale;
	init_pixel_y = matrix_y * scale;
    py = 0; 
	while (py < scale)
	{
        px = 0; 
		while (px < scale)
		{
			mlx_put_pixel(game->img, init_pixel_x + px, init_pixel_y + py, 0xFF000000);
            px++;
		}
        py++;
	}
    return (scale);
}

static void draw_character(t_game *game, int scale)
{
    int pixel_x;
    int pixel_y;
    int py;
    int px;

    pixel_x = (int)game->pos_x * scale;
    pixel_y = (int)game->pos_y * scale;
    py = 0;
    while(py < scale)
    {
        px = 0;
        while (px < scale)
        {
           mlx_put_pixel(game->img, pixel_x + px, pixel_y + py, 0xFFFFFFFF);
           px++; 
        }
        py++;
    }
}

void draw_minimap(void *param)
{
    int x;
    int y;
    int scale;
    t_game	*game;

	game = (t_game *)param;
    y = 0;
    while(y < game->map->height)
    {
        x = 0;
        while (x < game->map->width)
        {
            if (game->map->map[y][x] == '1')
            {
                scale = draw_mini_walls(game, x, y);
            }
            x++;
        }
        y++;
    }
    draw_character(game, scale);
}
