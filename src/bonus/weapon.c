#include "../../includes/cub3d.h"

void	update_weapon(t_game *game)
{
	if (game->weapon.state == WEAPON_SHOOT)
	{
		game->weapon.anim_timer--;
		if (game->weapon.anim_timer <= 0)
		{
			game->weapon.state = WEAPON_IDLE;
			game->weapon.anim_timer = 0;
		}
	}
}

void	draw_weapon(t_game *game)
{
	t_img	*tex;
	int		draw_w;
	int		draw_h;
	int		start_x;
	int		start_y;
	int		sy;
	int		sx;
	int		tx;
	int		ty;
	int		color;

	tex = &game->gun_tex;
	if (!tex->img)
		return ;
	draw_w = game->screen_w / 3;
	draw_h = game->screen_h / 2;
	start_x = (game->screen_w - draw_w) / 2;
	start_y = game->screen_h - draw_h;
	if (game->weapon.state == WEAPON_SHOOT)
		start_y += (game->weapon.anim_timer * 5);
	sy = 0;
	while (sy < draw_h)
	{
		sx = 0;
		while (sx < draw_w)
		{
			tx = sx * tex->width / draw_w;
			ty = sy * tex->height / draw_h;
			color = get_tex_pixel(tex, tx, ty);
			if ((color & 0xFFFFFF) > 0x101010)
				img_put_pixel(&game->screen, start_x + sx, start_y + sy, color);
			sx++;
		}
		sy++;
	}
}

static void	hit_enemy(t_game *game)
{
	int		i;
	double	sp_x;
	double	sp_y;
	double	inv_det;
	double	tx;
	double	ty;
	int		sx;

	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sprites[i].state >= ENEMY_DYING)
		{
			i++;
			continue ;
		}
		sp_x = game->sprites[i].pos_x - game->player.pos_x;
		sp_y = game->sprites[i].pos_y - game->player.pos_y;
		inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
				- game->player.dir_x * game->player.plane_y);
		tx = inv_det * (game->player.dir_y * sp_x - game->player.dir_x * sp_y);
		ty = inv_det * (-game->player.plane_y * sp_x
				+ game->player.plane_x * sp_y);
		if (ty <= 0.0)
		{
			i++;
			continue ;
		}
		sx = (int)((game->screen_w / 2) * (1.0 + tx / ty));
		if (sx >= game->screen_w / 2 - 30 && sx <= game->screen_w / 2 + 30
			&& ty < game->zbuffer[game->screen_w / 2])
		{
			game->sprites[i].hp -= 50;
			if (game->sprites[i].hp <= 0)
			{
				game->sprites[i].state = ENEMY_DYING;
				game->sprites[i].frame_timer = 0;
			}
		}
		i++;
	}
}

int	mouse_click(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)
		player_shoot(game);
	return (0);
}

void	player_shoot(t_game *game)
{
	if (game->weapon.state != WEAPON_IDLE)
		return ;
	game->weapon.state = WEAPON_SHOOT;
	game->weapon.anim_timer = 12;
	hit_enemy(game);
	
	spawn_bullet(game,
		game->player.pos_x + game->player.dir_x * 0.6,
		game->player.pos_y + game->player.dir_y * 0.6,
		game->player.dir_x, game->player.dir_y, 0);
}

void	draw_hud(t_game *game)
{
	int		bar_w;
	int		bar_h;
	int		bar_x;
	int		bar_y;
	int		fill_w;
	int		x;
	int		y;
	int		color;
	int		bg;

	bar_w = 300;
	bar_h = 20;
	bar_x = (game->screen_w - bar_w) / 2;
	bar_y = game->screen_h - 36;
	fill_w = bar_w * game->player_hp / 100;
	if (fill_w < 0)
		fill_w = 0;
	if (game->player_hp > 60)
		color = 0x22DD22;
	else if (game->player_hp > 30)
		color = 0xFFAA00;
	else
		color = 0xDD2222;
	bg = 0x222222;
	y = bar_y - 2;
	while (y < bar_y + bar_h + 2)
	{
		x = bar_x - 2;
		while (x < bar_x + bar_w + 2)
		{
			img_put_pixel(&game->screen, x, y, 0x111111);
			x++;
		}
		y++;
	}
	y = bar_y;
	while (y < bar_y + bar_h)
	{
		x = bar_x;
		while (x < bar_x + bar_w)
		{
			img_put_pixel(&game->screen, x, y,
				(x < bar_x + fill_w) ? color : bg);
			x++;
		}
		y++;
	}
}
