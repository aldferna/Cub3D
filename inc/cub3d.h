/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:53 by lumartin          #+#    #+#             */
/*   Updated: 2025/05/12 19:46:26 by lumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>

typedef struct s_player
{
	int			init_x;
	int			init_y;
	int			x;
	int			y;
	char		direction;
}				t_player;

typedef struct s_map
{
	int			width;
	int			height;
	char		**map;
	char		*path;
	char		*floor_color;
	int			f_col;
	char		*sky_color;
	int			s_col;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	t_player	*player;
}				t_map;

// PARSE
t_map			*init_map(char *map_path);
t_player		*init_player(t_map *map);

// CHECK MAP
int				check_map(t_map *map);

// UTILS
void			print_map(t_map *map);
void			print_map_copy(char **map_copy);

#endif