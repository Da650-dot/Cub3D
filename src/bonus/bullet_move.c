/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:21:58 by gabriede          #+#    #+#             */
/*   Updated: 2026/03/08 16:21:58 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	spawn_bullet(t_game *game)
{
	int		i;
	double	dx;
	double	dy;

	dx = game->player.dir_x;
	dy = game->player.dir_y;
	i = 0;
	while (i < BULLET_MAX)
	{
		if (!game->bullets[i].active)
		{
			game->bullets[i].pos_x = game->player.pos_x + dx * 0.05;
			game->bullets[i].pos_y = game->player.pos_y + dy * 0.05;
			game->bullets[i].dir_x = dx;
			game->bullets[i].dir_y = dy;
			game->bullets[i].active = 1;
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
			game->bullets[i].active = 0;
		i++;
	}
}
