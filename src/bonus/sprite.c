#include "../../includes/cub3d.h"


static void	sort_sprites(t_game *game)
{
	int			i;
	int			j;
	t_sprite	tmp;
	t_player	*p;

	p = &game->player;
	i = 0;
	while (i < game->sprite_count)
	{
		game->sprites[i].dist = ((p->pos_x - game->sprites[i].pos_x)
				* (p->pos_x - game->sprites[i].pos_x)
				+ (p->pos_y - game->sprites[i].pos_y)
				* (p->pos_y - game->sprites[i].pos_y));
		i++;
	}
	i = 0;
	while (i < game->sprite_count - 1)
	{
		j = i + 1;
		while (j < game->sprite_count)
		{
			if (game->sprites[i].dist < game->sprites[j].dist)
			{
				tmp = game->sprites[i];
				game->sprites[i] = game->sprites[j];
				game->sprites[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	render_sprite(t_game *game, t_sprite *sp)
{
	t_player	*p;
	t_img		*tex;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			sprite_width;
	int			draw_start_y;
	int			draw_end_y;
	int			draw_start_x;
	int			draw_end_x;
	int			stripe;
	int			y;
	int			dying;

	p = &game->player;
	dying = (sp->state == ENEMY_DYING);
	sprite_x = sp->pos_x - p->pos_x;
	sprite_y = sp->pos_y - p->pos_y;
	inv_det = 1.0 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y);
	transform_x = inv_det * (p->dir_y * sprite_x - p->dir_x * sprite_y);
	transform_y = inv_det * (-p->plane_y * sprite_x + p->plane_x * sprite_y);
	if (transform_y <= 0)
		return ;
	sprite_screen_x = (int)((WIN_W / 2) * (1 + transform_x / transform_y));
	sprite_height = abs((int)(WIN_H / transform_y));
	draw_start_y = -sprite_height / 2 + WIN_H / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = sprite_height / 2 + WIN_H / 2;
	if (draw_end_y >= WIN_H)
		draw_end_y = WIN_H - 1;
	sprite_width = abs((int)(WIN_H / transform_y));
	draw_start_x = -sprite_width / 2 + sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (draw_end_x >= WIN_W)
		draw_end_x = WIN_W - 1;
	tex = &game->tex[TEX_SPRITE].img;
	stripe = draw_start_x;
	while (stripe <= draw_end_x)
	{
		int	tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x))
				* tex->width / sprite_width) / 256;
		if (transform_y > 0 && stripe >= 0 && stripe < WIN_W
			&& transform_y < game->zbuffer[stripe])
		{
			y = draw_start_y;
			while (y <= draw_end_y)
			{
				int d = y * 256 - WIN_H * 128 + sprite_height * 128;
				int tex_y = ((d * tex->height) / sprite_height) / 256;
				int color = get_tex_pixel(tex, tex_x, tex_y);
				if (dying)
					color = ((color >> 1) & 0x007F7F) | 0xFF0000;
				if ((color & 0xFFFFFF) > 0x101010)
					img_put_pixel(&game->screen, stripe, y, color);
				y++;
			}
		}
		stripe++;
	}
}

void	draw_sprites(t_game *game)
{
	int	i;

	if (!game->sprites || game->sprite_count == 0)
		return ;
	sort_sprites(game);
	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sprites[i].state != ENEMY_DEAD)
			render_sprite(game, &game->sprites[i]);
		i++;
	}
}

void	update_enemies(t_game *game)
{
	int		i;
	double	dx;
	double	dy;
	double	dist;
	double	nx;
	double	ny;

	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sprites[i].state == ENEMY_DYING)
		{
			game->sprites[i].frame_timer++;
			if (game->sprites[i].frame_timer > 30)
				game->sprites[i].state = ENEMY_DEAD;
			i++;
			continue ;
		}
		if (game->sprites[i].state == ENEMY_DEAD)
		{
			i++;
			continue ;
		}
		dx = game->player.pos_x - game->sprites[i].pos_x;
		dy = game->player.pos_y - game->sprites[i].pos_y;
		dist = sqrt(dx * dx + dy * dy);
		if (dist < 8.0 && dist > 0.01)
		{
			game->sprites[i].state = ENEMY_CHASE;
			nx = game->sprites[i].pos_x + (dx / dist) * 0.025;
			ny = game->sprites[i].pos_y + (dy / dist) * 0.025;
			if (game->map.grid[(int)game->sprites[i].pos_y][(int)nx] != WALL
				&& game->map.grid[(int)game->sprites[i].pos_y][(int)nx]
				!= DOOR_CLOSED)
				game->sprites[i].pos_x = nx;
			if (game->map.grid[(int)ny][(int)game->sprites[i].pos_x] != WALL
				&& game->map.grid[(int)ny][(int)game->sprites[i].pos_x]
				!= DOOR_CLOSED)
				game->sprites[i].pos_y = ny;
			
			if (dist > 1.5 && dist < ENEMY_SHOOT_RANGE)
			{
				game->sprites[i].shoot_timer--;
				if (game->sprites[i].shoot_timer <= 0)
				{
					spawn_bullet(game,
						game->sprites[i].pos_x,
						game->sprites[i].pos_y, dx, dy, 1);
					game->sprites[i].shoot_timer = ENEMY_SHOOT_CD;
				}
			}
			
			if (dist < 0.7 && game->hit_timer <= 0)
			{
				game->player_hp -= 10;
				if (game->player_hp < 0)
					game->player_hp = 0;
				game->hit_timer = 40;
			}
		}
		else
			game->sprites[i].state = ENEMY_IDLE;
		i++;
	}
	if (game->hit_timer > 0)
		game->hit_timer--;
}
