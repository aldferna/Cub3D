/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldara <aldara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:53 by lumartin          #+#    #+#             */
/*   Updated: 2025/06/06 21:21:46 by aldara           ###   ########.fr       */
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

/**
 * @param pos_x and pos_y: Player position, ex; (2.5, 2.5)
 * @param dir_x and dir_y: Initial direction vector according to character orientation
 * @param plane_x and plane_y: Perpendicular vector to the previous one (width vision)
 */
typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			*map;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rot_speed;
	double			scroll_speed;
	mlx_texture_t	*north_tex;
	mlx_texture_t	*south_tex;
	mlx_texture_t	*east_tex;
	mlx_texture_t	*west_tex;
}					t_game;

/**
 * @param camera_x: Proportion used to angle the ray right/left (-1 to 1)
 * @param ray_dir_x and ray_dir_y: Ray's direction vector
 * @param delta_dist_x and delta_dist_y: Distance to reach next horizontal/vertical line (hipotenuse)
 * @param map_x and map_y: Ray's position as it moves forward
 * @param step_x and step_y: Direction taken by the rays but in 1/-1 format (moves forward/backwards map_x/y)
 * @param side_dist_x and side_dist_y: Distance to ‘touch’ the next X/Y line from player coord
 * @param side: Whether the beam moves forward through a X/Y line (side = 0 - crosses a vertical line)
 * @param perp_wall_dist: Distance between camera plane (not player spot) and wall
 * @param line_height: Wall height
 * @param draw_start and draw_end: Where to start/end drawing the vertical line (wall)
 * @param wall_x: exact point where ray hits the wall (left edge: 0.00 - right edge: 1.00)
 * @param tex_dir: Texture that has to be draw dependin on orientation
 * @param tex_x: Texture X column to use
 */
typedef struct s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	double			side_dist_x;
	double			side_dist_y;
	int				side;
	int				hit;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_dir;
	int				tex_x;
	uint32_t		color;
}					t_ray;

// PARSE
t_map				*init_map(char *map_path, t_map *map);
void 				init_player(t_map *map);
int					check_map(t_map *map);
int					is_map_surrounded(t_map *map);
int					create_color(char *str_color);
int					check_textures(t_map map);
void				set_witdh_height(t_map *map);
void				replace_spaces(t_map *map);

// GAME
int					start_game(t_map *map);
void				handle_keys(void *param);
void 				scroll(double xdelta, double ydelta, void* param);
void 				delete_textures(t_game *game);
void				handle_close(void *param);
void				render_frame(void *param);
void				load_textures(t_game *game);

// DDA
void				init_direction(t_game *game);
void				init_ray(t_game *game, t_ray *ray, int x);
void				calc_step_and_side_dist(t_game *game, t_ray *ray);
void				perform_dda(t_game *game, t_ray *ray);

// DRAW WALL
void				calc_wall_height_and_texture(t_game *game, t_ray *ray);
void				draw_wall_line(t_game *game, t_ray *ray, int x);

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
void				free_map_copy(char **map_copy, int height);
int					get_width(char *line);
void 				ft_strcpy_fillmap(t_map *map, int i, char *str, int lenght);

#endif