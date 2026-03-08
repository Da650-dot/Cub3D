/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:25:26 by gabriede          #+#    #+#             */
/*   Updated: 2026/03/08 16:25:26 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	rotate_view(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

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
}

int	mouse_move(int x, int y, t_game *game)
{
	int		delta_x;
	double	angle;

	(void)y;
	delta_x = x - game->mouse_x;
	game->mouse_x = x;
	if (x < game->screen_w / 4 || x > game->screen_w * 3 / 4)
	{
		mlx_mouse_move(game->mlx, game->win,
			game->screen_w / 2, game->screen_h / 2);
		game->mouse_x = game->screen_w / 2;
	}
	if (delta_x == 0)
		return (0);
	angle = delta_x * ROT_SPEED * 0.3;
	rotate_view(game, angle);
	return (0);
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
	spawn_bullet(game);
}
