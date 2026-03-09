/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:23:10 by gabriede          #+#    #+#             */
/*   Updated: 2026/03/08 16:23:10 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	toggle_door_at(t_game *game, int fx, int fy)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].map_x == fx && game->doors[i].map_y == fy)
		{
			game->doors[i].open = !game->doors[i].open;
			return (1);
		}
		i++;
	}
	return (0);
}

void	interact_door(t_game *game)
{
	t_player	*p;
	double		step;
	int			front_x;
	int			front_y;

	p = &game->player;
	step = 0.5;
	while (step <= 2.5)
	{
		front_x = (int)(p->pos_x + p->dir_x * step);
		front_y = (int)(p->pos_y + p->dir_y * step);
		if (toggle_door_at(game, front_x, front_y))
			return ;
		step += 0.5;
	}
}

static void	update_door_state(t_game *game, int i, double speed)
{
	if (game->doors[i].open && game->doors[i].open_pct < 1.0)
	{
		game->doors[i].open_pct += speed;
		if (game->doors[i].open_pct >= 1.0)
		{
			game->doors[i].open_pct = 1.0;
			game->map.grid[game->doors[i].map_y]
			[game->doors[i].map_x] = DOOR_OPEN;
		}
	}
	else if (!game->doors[i].open && game->doors[i].open_pct > 0.0)
	{
		game->doors[i].open_pct -= speed;
		if (game->doors[i].open_pct <= 0.0)
		{
			game->doors[i].open_pct = 0.0;
			game->map.grid[game->doors[i].map_y]
			[game->doors[i].map_x] = DOOR_CLOSED;
		}
	}
}

void	update_doors(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		update_door_state(game, i, 0.03);
		i++;
	}
}
