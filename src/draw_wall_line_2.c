/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_line_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:00:41 by aldara            #+#    #+#             */
/*   Updated: 2025/06/05 12:51:51 by lumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static uint32_t	set_tex_col(mlx_texture_t *tex, double *tex_pos,
		double step_scale, t_ray *ray)
{
	uint32_t	*pixels;
	uint32_t	color;
	int			tex_y;
	int			rgb[3];

	tex_y = (int)(*tex_pos) % tex->height;
	(*tex_pos) += step_scale;
	pixels = (uint32_t *)tex->pixels;
	color = pixels[tex->width * tex_y + ray->tex_x];
	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = color & 0xFF;
	color = (rgb[2] << 24) | (rgb[1] << 16) | (rgb[0] << 8) | 255;
	return (color);
}

/**
 * @brief Draws the vertical line of the wall with its corresponding texture.
 */
void	draw_wall_line(t_game *game, t_ray *ray, int x)
{
	int				y;
	mlx_texture_t	*tex;
	double			step_scale;
	double			tex_pos;
	uint32_t		color;

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
		color = set_tex_col(tex, &tex_pos, step_scale, ray);
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}
