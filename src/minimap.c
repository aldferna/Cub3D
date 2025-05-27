/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldara <aldara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:57:04 by aldara            #+#    #+#             */
/*   Updated: 2025/05/27 21:41:00 by aldara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void draw_lines(t_game *game, int x, int y)
{
    int scale;

    scale = 10;
    
    while ((game->map->width * scale) > WIDTH / 4 || (game->map->height *scale) > HEIGHT / 4)
        scale--;
    
    y = (y * scale) + scale;
    while (y > (y * scale))
    {
        x = (x * scale) + scale;
        while (x > (x * scale))
        {
            mlx_put_pixel(game->img, x, y, 0xFF000000);
            x--;
        }
        y--;
    }
} */

void draw_lines(t_game *game, int map_x, int map_y)
{
	int px;
    int py;
    int init_pixel_x;
    int init_pixel_y;
	int scale;

    scale = 10;
	while ((game->map->width * scale) > (WIDTH / 4) || (game->map->height * scale) > (HEIGHT / 4))
		scale--;
	init_pixel_x = map_x * scale;
	init_pixel_y = map_y * scale;
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
}


void draw_minimap(void *param)
{
    int x;
    int y;
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
                draw_lines(game, x, y);
            }
            x++;
        }
        y++;
    }
}
