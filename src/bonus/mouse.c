#include "../../includes/cub3d.h"

int	mouse_move(int x, int y, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;
	int		delta_x;

	(void)y;
	delta_x = x - game->mouse_x;
	game->mouse_x = x;
	
	if (x < game->screen_w / 4 || x > game->screen_w * 3 / 4)
	{
		mlx_mouse_move(game->mlx, game->win, game->screen_w / 2, game->screen_h / 2);
		game->mouse_x = game->screen_w / 2;
	}
	if (delta_x == 0)
		return (0);
	angle = delta_x * ROT_SPEED * 0.3;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
	return (0);
}
