/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldara <aldara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:53 by lumartin          #+#    #+#             */
/*   Updated: 2025/06/01 19:08:12 by aldara           ###   ########.fr       */
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
	double			delta_dist_x; //cuanto debe avanzar para llegar a la siguiente X
	double			delta_dist_y;
	int				map_x; //donde se encuentra el rayo mientras avanza
	int				map_y;
	int				step_x; //direccion que toman los rayos pero en formato 1/-1 (hace avanzar/retro map_x/y)
	int				step_y;
	double			side_dist_x; //distancia que falta para 'tocar' el siguiente lado X/ Y
	double			side_dist_y; //van acumulando lo q se va recorriendo
	int				side; //si el rayo avanza cruzando a trves de X o a traves de Y
	int				hit;
	double			perp_wall_dist; //dst entre plano de camara (no personaje) y pared
	int				line_height; //altura pared
	int				draw_start; // Y inicial de la pared
	int				draw_end; // Y final
	double			wall_x; //p exacto donde rayo golpea la pared (entre 0.0 y 1.0-> 0.0 borde izq/0.99 drch
	int				tex_dir; //cara/orientacion q hay q dibujar
	int				tex_x; //que columna de la textura usar
	uint32_t		color;
}					t_ray;

// PARSE
t_map				*init_map(char *map_path);
t_player			*init_player(t_map *map);
int					check_map(t_map *map);

// GAME
int					start_game(t_map *map);
void				handle_movement(void *param);

// MINIMAP
void 				draw_minimap(void *param);
void 				draw_mini_ray(t_game *game, t_ray ray);
void				draw_line_v(int x_init, int y_init, int *x_y_end, t_game *game);
void				draw_line_h(int x_init, int y_init, int *x_y_end, t_game *game);

// UTILS
void				print_map(t_map *map);
void				print_map_copy(char **map_copy);
void				clean_buffer(int fd);
void 				free_resources(t_map *map);

#endif