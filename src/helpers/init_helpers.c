/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:11:07 by gabriede          #+#    #+#             */
/*   Updated: 2026/03/08 15:37:15 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_init_player_direction(t_player *p, double *directions)
{
	p->dir_x = directions[0];
	p->dir_y = directions[1];
	p->plane_x = directions[2];
	p->plane_y = directions[3];
}

void	fill_doors(t_game *game)
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

int	count_doors(t_game *game)
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

int	load_one_texture(t_game *game, int i)
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
