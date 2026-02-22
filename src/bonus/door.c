#include "../../includes/cub3d.h"

void	interact_door(t_game *game)
{
	t_player	*p;
	int			i;
	int			front_x;
	int			front_y;
	double		step;

	p = &game->player;
	step = 0.5;
	while (step <= 2.5)
	{
		front_x = (int)(p->pos_x + p->dir_x * step);
		front_y = (int)(p->pos_y + p->dir_y * step);
		i = 0;
		while (i < game->door_count)
		{
			if (game->doors[i].map_x == front_x
				&& game->doors[i].map_y == front_y)
			{
				game->doors[i].open = !game->doors[i].open;
				return ;
			}
			i++;
		}
		step += 0.5;
	}
}

void	update_doors(t_game *game)
{
	int		i;
	double	speed;

	speed = 0.05;
	i = 0;
	while (i < game->door_count)
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
		i++;
	}
}
