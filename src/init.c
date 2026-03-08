/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:09:17 by gabriede          #+#    #+#             */
/*   Updated: 2026/03/08 15:09:17 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player_direction(t_player *p, char dir)
{
	if (dir == 'N')
		set_init_player_direction(p, (double []){0, -1, 0.66, 0});
	else if (dir == 'S')
		set_init_player_direction(p, (double []){0, 1, -0.66, 0});
	else if (dir == 'E')
		set_init_player_direction(p, (double []){1, 0, 0, 0.66});
	else
		set_init_player_direction(p, (double []){-1, 0, 0, -0.66});
}

int	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (game->map.tex_path[i] && !load_one_texture(game, i))
			return (0);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (!game->tex[i].img.img)
			return (0);
		i++;
	}
	return (1);
}

int	init_doors(t_game *game)
{
	int	count;

	count = count_doors(game);
	game->door_count = count;
	if (count == 0)
		return (1);
	game->doors = (t_door *)malloc(sizeof(t_door) * count);
	if (!game->doors)
		return (0);
	fill_doors(game);
	return (1);
}

int	init_screen(t_game *game)
{
	game->screen.img = mlx_new_image(game->mlx, game->screen_w, game->screen_h);
	if (!game->screen.img)
		return (0);
	game->screen.width = game->screen_w;
	game->screen.height = game->screen_h;
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bits_per_pixel,
			&game->screen.line_len,
			&game->screen.endian);
	return (game->screen.addr != NULL);
}

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	mlx_get_screen_size(game->mlx, &game->screen_w, &game->screen_h);
	game->screen_w = game->screen_w * 98 / 100;
	game->screen_h = game->screen_h * 98 / 100;
	game->zbuffer = (double *)malloc(sizeof(double) * game->screen_w);
	if (!game->zbuffer)
		return (0);
	game->win = mlx_new_window(game->mlx,
			game->screen_w, game->screen_h, WIN_TITLE);
	if (!game->win)
		return (0);
	return (init_screen(game));
}
