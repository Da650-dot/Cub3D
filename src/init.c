#include "../includes/cub3d.h"

void	init_player_direction(t_player *p, char dir)
{
	if (dir == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (dir == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	else if (dir == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

int	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (!game->map.tex_path[i])
		{
			i++;
			continue ;
		}
		game->tex[i].img.img = mlx_xpm_file_to_image(game->mlx,
				game->map.tex_path[i],
				&game->tex[i].img.width,
				&game->tex[i].img.height);
		if (!game->tex[i].img.img)
			return (0);
		game->tex[i].img.addr = mlx_get_data_addr(game->tex[i].img.img,
				&game->tex[i].img.bits_per_pixel,
				&game->tex[i].img.line_len,
				&game->tex[i].img.endian);
		if (!game->tex[i].img.addr)
			return (0);
		i++;
	}
	
	i = 0;
	while (i < 4)
	{
		if (!game->tex[i].img.img)
			return (0);
		i++;
	}
	return (1);
}

int	init_sprites(t_game *game)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == SPRITE_CHAR)
				count++;
			x++;
		}
		y++;
	}
	game->sprite_count = count;
	if (count == 0)
		return (1);
	game->sprites = (t_sprite *)malloc(sizeof(t_sprite) * count);
	if (!game->sprites)
		return (0);
	count = 0;
	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == SPRITE_CHAR)
			{
				game->sprites[count].pos_x = x + 0.5;
				game->sprites[count].pos_y = y + 0.5;
				game->sprites[count].dist = 0;
				game->sprites[count].frame_timer = 0;
				game->sprites[count].state = ENEMY_IDLE;
				game->sprites[count].hp = 100;
				game->sprites[count].shoot_timer = ENEMY_SHOOT_CD;
				game->map.grid[y][x] = EMPTY;
				count++;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	init_doors(t_game *game)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == DOOR_CLOSED)
				count++;
			x++;
		}
		y++;
	}
	game->door_count = count;
	if (count == 0)
		return (1);
	game->doors = (t_door *)malloc(sizeof(t_door) * count);
	if (!game->doors)
		return (0);
	count = 0;
	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == DOOR_CLOSED)
			{
				game->doors[count].map_x = x;
				game->doors[count].map_y = y;
				game->doors[count].open = 0;
				game->doors[count].open_pct = 0.0;
				count++;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	mlx_get_screen_size(game->mlx, &game->screen_w, &game->screen_h);
	game->zbuffer = (double *)malloc(sizeof(double) * game->screen_w);
	if (!game->zbuffer)
		return (0);
	game->win = mlx_new_window(game->mlx, game->screen_w, game->screen_h, WIN_TITLE);
	if (!game->win)
		return (0);
	game->screen.img = mlx_new_image(game->mlx, game->screen_w, game->screen_h);
	if (!game->screen.img)
		return (0);
	game->screen.width = game->screen_w;
	game->screen.height = game->screen_h;
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bits_per_pixel,
			&game->screen.line_len,
			&game->screen.endian);
	if (!game->screen.addr)
		return (0);
	game->weapon.state = WEAPON_IDLE;
	game->weapon.anim_timer = 0;
	game->player_hp = 100;
	game->hit_timer = 0;
	return (1);
}

int	load_gun_texture(t_game *game)
{
	game->gun_tex.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/gun.xpm",
			&game->gun_tex.width,
			&game->gun_tex.height);
	if (!game->gun_tex.img)
		return (0);
	game->gun_tex.addr = mlx_get_data_addr(game->gun_tex.img,
			&game->gun_tex.bits_per_pixel,
			&game->gun_tex.line_len,
			&game->gun_tex.endian);
	if (!game->gun_tex.addr)
		return (0);
	return (1);
}
