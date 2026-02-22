#include "../../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	if (keycode == KEY_W)
		game->player.move_forward = 1;
	if (keycode == KEY_S)
		game->player.move_back = 1;
	if (keycode == KEY_A)
		game->player.move_left = 1;
	if (keycode == KEY_D)
		game->player.move_right = 1;
	if (keycode == KEY_LEFT)
		game->player.rot_left = 1;
	if (keycode == KEY_RIGHT)
		game->player.rot_right = 1;
	if (keycode == KEY_E)
		player_shoot(game);
	if (keycode == KEY_SPACE)
		interact_door(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.move_forward = 0;
	if (keycode == KEY_S)
		game->player.move_back = 0;
	if (keycode == KEY_A)
		game->player.move_left = 0;
	if (keycode == KEY_D)
		game->player.move_right = 0;
	if (keycode == KEY_LEFT)
		game->player.rot_left = 0;
	if (keycode == KEY_RIGHT)
		game->player.rot_right = 0;
	return (0);
}

static void	rotate_player(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

static int	can_move(t_game *game, double new_x, double new_y)
{
	int		ix;
	int		iy;
	char	c;

	ix = (int)new_x;
	iy = (int)new_y;
	if (iy < 0 || iy >= game->map.rows)
		return (0);
	if (ix < 0 || ix >= (int)ft_strlen(game->map.grid[iy]))
		return (0);
	c = game->map.grid[iy][ix];
	if (c == WALL || c == DOOR_CLOSED || c == ' ')
		return (0);
	return (1);
}

void	move_player(t_game *game)
{
	t_player	*p;
	double		spd;

	p = &game->player;
	spd = MOVE_SPEED;
	if (p->move_forward)
	{
		if (can_move(game, p->pos_x + p->dir_x * spd, p->pos_y))
			p->pos_x += p->dir_x * spd;
		if (can_move(game, p->pos_x, p->pos_y + p->dir_y * spd))
			p->pos_y += p->dir_y * spd;
	}
	if (p->move_back)
	{
		if (can_move(game, p->pos_x - p->dir_x * spd, p->pos_y))
			p->pos_x -= p->dir_x * spd;
		if (can_move(game, p->pos_x, p->pos_y - p->dir_y * spd))
			p->pos_y -= p->dir_y * spd;
	}
	if (p->move_left)
	{
		if (can_move(game, p->pos_x - p->plane_x * spd, p->pos_y))
			p->pos_x -= p->plane_x * spd;
		if (can_move(game, p->pos_x, p->pos_y - p->plane_y * spd))
			p->pos_y -= p->plane_y * spd;
	}
	if (p->move_right)
	{
		if (can_move(game, p->pos_x + p->plane_x * spd, p->pos_y))
			p->pos_x += p->plane_x * spd;
		if (can_move(game, p->pos_x, p->pos_y + p->plane_y * spd))
			p->pos_y += p->plane_y * spd;
	}
	if (p->rot_left)
		rotate_player(p, -ROT_SPEED);
	if (p->rot_right)
		rotate_player(p, ROT_SPEED);
}
