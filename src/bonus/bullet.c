#include "../../includes/cub3d.h"

void	spawn_bullet(t_game *game, double px, double py,
		double dx, double dy, int is_enemy)
{
	int		i;
	double	len;

	len = sqrt(dx * dx + dy * dy);
	if (len < 0.0001)
		return ;
	i = 0;
	while (i < BULLET_MAX)
	{
		if (!game->bullets[i].active)
		{
			game->bullets[i].pos_x = px;
			game->bullets[i].pos_y = py;
			game->bullets[i].dir_x = dx / len;
			game->bullets[i].dir_y = dy / len;
			game->bullets[i].active = 1;
			game->bullets[i].is_enemy = is_enemy;
			return ;
		}
		i++;
	}
}

static int	bullet_hits_wall(t_game *game, double bx, double by)
{
	int		ix;
	int		iy;
	char	c;

	ix = (int)bx;
	iy = (int)by;
	if (iy < 0 || iy >= game->map.rows)
		return (1);
	if (ix < 0 || ix >= (int)ft_strlen(game->map.grid[iy]))
		return (1);
	c = game->map.grid[iy][ix];
	return (c == WALL || c == DOOR_CLOSED || c == ' ');
}

static void	check_player_hit(t_game *game, t_bullet *b)
{
	double	dx;
	double	dy;

	dx = b->pos_x - game->player.pos_x;
	dy = b->pos_y - game->player.pos_y;
	if ((dx * dx + dy * dy) < 0.25)
	{
		b->active = 0;
		if (game->hit_timer <= 0)
		{
			game->player_hp -= 15;
			if (game->player_hp < 0)
				game->player_hp = 0;
			game->hit_timer = 45;
		}
	}
}

static void	check_enemy_hit(t_game *game, t_bullet *b)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sprites[i].state >= ENEMY_DYING)
		{
			i++;
			continue ;
		}
		dx = b->pos_x - game->sprites[i].pos_x;
		dy = b->pos_y - game->sprites[i].pos_y;
		if ((dx * dx + dy * dy) < 0.25)
		{
			b->active = 0;
			game->sprites[i].hp -= 50;
			if (game->sprites[i].hp <= 0)
			{
				game->sprites[i].state = ENEMY_DYING;
				game->sprites[i].frame_timer = 0;
			}
			return ;
		}
		i++;
	}
}

void	update_bullets(t_game *game)
{
	int	i;

	i = 0;
	while (i < BULLET_MAX)
	{
		if (!game->bullets[i].active)
		{
			i++;
			continue ;
		}
		game->bullets[i].pos_x += game->bullets[i].dir_x * BULLET_SPEED;
		game->bullets[i].pos_y += game->bullets[i].dir_y * BULLET_SPEED;
		if (bullet_hits_wall(game,
				game->bullets[i].pos_x, game->bullets[i].pos_y))
		{
			game->bullets[i].active = 0;
			i++;
			continue ;
		}
		if (game->bullets[i].is_enemy)
			check_player_hit(game, &game->bullets[i]);
		else
			check_enemy_hit(game, &game->bullets[i]);
		i++;
	}
}

static void	draw_one_bullet(t_game *game, t_bullet *b)
{
	double	sp_x;
	double	sp_y;
	double	inv_det;
	double	tx;
	double	ty;
	int		screen_x;
	int		h;
	int		ds_y;
	int		de_y;
	int		sx;
	int		sy;
	int		color;

	sp_x = b->pos_x - game->player.pos_x;
	sp_y = b->pos_y - game->player.pos_y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	tx = inv_det * (game->player.dir_y * sp_x - game->player.dir_x * sp_y);
	ty = inv_det * (-game->player.plane_y * sp_x
			+ game->player.plane_x * sp_y);
	if (ty <= 0.1)
		return ;
	screen_x = (int)((WIN_W / 2) * (1.0 + tx / ty));
	h = abs((int)(WIN_H / ty / 8));
	if (h < 4)
		h = 4;
	if (h > 30)
		h = 30;
	ds_y = WIN_H / 2 - h / 2;
	de_y = WIN_H / 2 + h / 2;
	color = b->is_enemy ? 0xFF4400 : 0xFFFF00;
	sy = ds_y;
	while (sy <= de_y)
	{
		sx = screen_x - h / 2;
		while (sx <= screen_x + h / 2)
		{
			if (sx >= 0 && sx < WIN_W && sy >= 0 && sy < WIN_H
				&& ty < game->zbuffer[sx])
				img_put_pixel(&game->screen, sx, sy, color);
			sx++;
		}
		sy++;
	}
}

void	draw_bullets(t_game *game)
{
	int	i;

	i = 0;
	while (i < BULLET_MAX)
	{
		if (game->bullets[i].active)
			draw_one_bullet(game, &game->bullets[i]);
		i++;
	}
}
