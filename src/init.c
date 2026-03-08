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
	else
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

static int	load_one_texture(t_game *game, int i)
{
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
	return (game->tex[i].img.addr != NULL);
}

int	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (game->map.tex_path[i] && !load_one_texture(game, i))
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

static int	count_doors(t_game *game)
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
	return (count);
}

static void	fill_doors(t_game *game)
{
	int	x;
	int	y;
	int	n;

	n = 0;
	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == DOOR_CLOSED)
			{
				game->doors[n].map_x = x;
				game->doors[n].map_y = y;
				game->doors[n].open = 0;
				game->doors[n].open_pct = 0.0;
				n++;
			}
			x++;
		}
		y++;
	}
}

int	init_doors(t_game *game)
{
	int	count;

	count = count_doors(game);
	game->door_count = count;
	if (count == 0)
		return (1);
	game->doors = (t_door *)malloc(sizeof(t_door) * count);
	if (!game->doors)
		return (0);
	fill_doors(game);
	return (1);
}

static int	init_screen(t_game *game)
{
	game->screen.img = mlx_new_image(game->mlx, game->screen_w, game->screen_h);
	if (!game->screen.img)
		return (0);
	game->screen.width = game->screen_w;
	game->screen.height = game->screen_h;
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bits_per_pixel,
			&game->screen.line_len,
			&game->screen.endian);
	return (game->screen.addr != NULL);
}

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	mlx_get_screen_size(game->mlx, &game->screen_w, &game->screen_h);
	game->screen_w = game->screen_w * 98 / 100;
	game->screen_h = game->screen_h * 98 / 100;
	game->zbuffer = (double *)malloc(sizeof(double) * game->screen_w);
	if (!game->zbuffer)
		return (0);
	game->win = mlx_new_window(game->mlx,
			game->screen_w, game->screen_h, WIN_TITLE);
	if (!game->win)
		return (0);
	return (init_screen(game));
}
