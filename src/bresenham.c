/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldara <aldara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:40:45 by aldara            #+#    #+#             */
/*   Updated: 2025/06/01 19:16:26 by aldara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_direction(int delta)
{
	int	dir;

	if (delta < 0)
		dir = -1;
	else
		dir = 1;
	return (dir);
}

void	swap_coordenates(int *x_init, int *y_init, int *x_y_end, char line)
{
	int	aux;

	if ((*x_init) <= x_y_end[0] && line == 'h')
		return ;
    if ((*y_init) <= x_y_end[1] && line == 'v')
		return ;
	aux = (*x_init);
	(*x_init) = x_y_end[0];
	x_y_end[0] = aux;
	aux = (*y_init);
	(*y_init) = x_y_end[1];
	x_y_end[1] = aux;
}

void	draw_line_v(int x_init, int y_init, int *x_y_end, t_game *game)
{
	int	p;
	int	i;
	int	dir;
	int	dx;
	int	dy;

	swap_coordenates(&x_init, &y_init, x_y_end, 'v');
	dx = x_y_end[0] - x_init;
	dy = x_y_end[1] - y_init;
	dir = check_direction(dx);
	dx *= dir;
	i = 0;
	p = 2 * dx - dy;
	while (i < abs(dy))
	{
		y_init += 1;
		if (p >= 0)
		{
			x_init += dir;
			p = p - 2 * dy;
		}
		p = p + 2 * dx;
		mlx_put_pixel(game->img, x_init, y_init, 0x55FFFFFF);
		i++;
	}
}

void	draw_line_h(int x_init, int y_init, int *x_y_end, t_game *game)
{
	int	p;
	int	i;
	int	dir;
	int	dx;
	int	dy;

	swap_coordenates(&x_init, &y_init, x_y_end, 'h');
	dx = x_y_end[0] - x_init;
	dy = x_y_end[1] - y_init;
	dir = check_direction(dy);
	dy *= dir;
	i = 0;
	p = 2 * dy - dx;
	while (i < abs(dx))
	{
		x_init += 1;
		if (p >= 0)
		{
			y_init += dir;
			p = p - 2 * dx;
		}
		p = p + 2 * dy;
		mlx_put_pixel(game->img, x_init, y_init, 0x55FFFFFF);
		i++;
	}
}
