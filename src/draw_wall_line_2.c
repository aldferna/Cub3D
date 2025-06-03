/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_line_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldara <aldara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:00:41 by aldara            #+#    #+#             */
/*   Updated: 2025/06/03 15:03:53 by aldara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void my_put_pixel()
{
    
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
