/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldara <aldara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:53 by lumartin          #+#    #+#             */
/*   Updated: 2025/05/13 17:45:06 by aldara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>

# define WIDTH 800
# define HEIGHT 600

typedef struct s_player
{
	int				init_x;
	int				init_y;
	char			direction;
}					t_player;

typedef struct s_map
{
	int				width;
	int				height;
	char			**map;
	char			*path;
	char			*floor_color;
	int				f_col;
	char			*sky_color;
	int				s_col;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	t_player		*player;
}					t_map;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			*map;
	double			pos_x; //posicion 'real' del personaje ((2.5, 2.5) si en el centro de celda 2,2)
	double			pos_y;
	double			dir_x; //vector dir (delta x) inicial segun orientacion personaje
	double			dir_y;
	double			plane_x; //vector perpendicular al vector anterior (ancho vision)
	double			plane_y;
	double			move_speed;
	double			rot_speed;
	mlx_texture_t	*north_tex;
	mlx_texture_t	*south_tex;
	mlx_texture_t	*east_tex;
	mlx_texture_t	*west_tex;
}					t_game;

typedef struct s_ray
{
	double			camera_x; //proporcion usada para angular rayo a derecha/izquierda (-1 a 1)
	double			ray_dir_x; //vector dir rayo lanzado (delta x)
	double			ray_dir_y;
	double			delta_dist_x; //prop avanza en X por cada paso ('crecimiento' del rayo segun dir)
	double			delta_dist_y;
	int				map_x; //pos 'real' de personaje a enteros
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	uint32_t		color;
	double			wall_x;
	int				tex_x;
	int				tex_dir;
}					t_ray;

// PARSE
t_map				*init_map(char *map_path);
t_player			*init_player(t_map *map);

// CHECK MAP
int					check_map(t_map *map);

// UTILS
void				print_map(t_map *map);
void				print_map_copy(char **map_copy);

// GAME
int					start_game(t_map *map);
void	handle_movement(void *param);

#endif