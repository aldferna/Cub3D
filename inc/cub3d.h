/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumartin <lumartin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:53 by lumartin          #+#    #+#             */
/*   Updated: 2025/05/09 18:21:11 by lumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>

typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
	char	*path;
	char	*floor_color;
	char	*sky_color;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
}			t_map;

//PARSE
t_map		*init_map(char *map_path);
int			check_name_map(char *str);

//UTILS
void		print_map(t_map *map);

#endif