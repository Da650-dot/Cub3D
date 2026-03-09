/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:01:01 by gabriede          #+#    #+#             */
/*   Updated: 2026/03/08 15:01:01 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define WIN_W        1280
# define WIN_H        720
# define WIN_TITLE    "cub3D"

# define MOVE_SPEED   0.01
# define ROT_SPEED    0.01

# define KEY_W        119
# define KEY_A        97
# define KEY_S        115
# define KEY_D        100
# define KEY_LEFT     65361
# define KEY_RIGHT    65363
# define KEY_ESC      65307
# define KEY_E        101
# define KEY_SPACE    32

# define WALL         '1'
# define EMPTY        '0'
# define DOOR_CLOSED  'D'
# define DOOR_OPEN    'O'

# define BULLET_MAX   32
# define BULLET_SPEED 0.15

# define NO           0
# define SO           1
# define WE           2
# define EA           3
# define TEX_DOOR     4
# define TEX_COUNT    5

# define MM_SCALE     5
# define MM_OFFSET_X  10
# define MM_OFFSET_Y  10
# define MM_WALL_CLR  0xAAAAAA
# define MM_FLOOR_CLR 0x333333
# define MM_PLAYER    0xFF4444
# define MM_DOOR_CLR  0xFFAA00

# define ERR_ARGS     "Usage: ./cub3D <map.cub>"
# define ERR_EXT      "Map file must have .cub extension"
# define ERR_OPEN     "Could not open map file"
# define ERR_MAP      "Invalid map"
# define ERR_WALL     "Map is not surrounded by walls"
# define ERR_PLAYER   "Invalid player position (missing or multiple)"
# define ERR_TEX      "Invalid or missing texture"
# define ERR_COLOR    "Invalid floor/ceiling color"
# define ERR_MLX      "MLX initialization failed"
# define ERR_MALLOC   "Memory allocation failed"

typedef struct s_bullet
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	int			active;
}	t_bullet;

typedef struct s_door
{
	int			map_x;
	int			map_y;
	int			open;
	double		open_pct;
}	t_door;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}	t_img;

typedef struct s_texture
{
	t_img		img;
}	t_texture;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			move_forward;
	int			move_back;
	int			move_left;
	int			move_right;
	int			rot_left;
	int			rot_right;
	int			interact;
}	t_player;

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	int			tex_num;
}	t_ray;

typedef struct s_map
{
	char		**grid;
	int			rows;
	int			cols;
	char		*tex_path[TEX_COUNT];
	int			floor_color;
	int			ceil_color;
	int			has_floor;
	int			has_ceil;
	int			has_tex[TEX_COUNT];
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_texture	tex[TEX_COUNT];
	t_player	player;
	t_map		map;
	int			screen_w;
	int			screen_h;
	double		*zbuffer;
	t_door		*doors;
	int			door_count;
	int			mouse_x;
	t_bullet	bullets[BULLET_MAX];
}	t_game;

int		parse_file(t_game *game, const char *path);
int		parse_map(t_game *game, char **lines, int start);
int		parse_elements(t_game *game, char **lines, int *idx);
int		parse_texture(t_map *map, char *line);
int		parse_color(t_map *map, char *line, int r, int g);
int		parse_checkers(t_game *game, char **lines, int start, int rows);

int		init_game(t_game *game);
int		load_textures(t_game *game);
void	init_player_direction(t_player *p, char dir);
int		init_doors(t_game *game);
int		count_doors(t_game *game);
void	fill_doors(t_game *game);
int		init_screen(t_game *game);
int		load_one_texture(t_game *game, int i);
void	set_init_player_direction(t_player *p, double *directions);

void	raycasting(t_game *game);
void	cast_ray(t_game *game, t_ray *ray, int x);
void	calc_wall(t_game *game, t_ray *ray);
int		dda_check(t_game *game, t_ray *ray);
void	draw_column(t_game *game, t_ray *ray, int x, int y);
void	draw_floor_ceiling(t_game *game);

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	move_player(t_game *game);

int		render(t_game *game);
void	img_put_pixel(t_img *img, int x, int y, int color);
int		get_tex_pixel(t_img *img, int x, int y);

void	draw_minimap(t_game *game);
void	update_doors(t_game *game);
void	interact_door(t_game *game);
int		mouse_move(int x, int y, t_game *game);
int		mouse_click(int button, int x, int y, t_game *game);
void	spawn_bullet(t_game *game);
void	update_bullets(t_game *game);
void	draw_bullets(t_game *game);

void	free_game(t_game *game);
void	error_exit(t_game *game, const char *msg);
char	**read_file_lines(const char *path);
void	free_strarr(char **arr);
int		strarr_len(char **arr);

int		close_window(t_game *game);

#endif
