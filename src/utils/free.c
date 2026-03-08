/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:42:31 by gabriede          #+#    #+#             */
/*   Updated: 2026/03/08 18:42:31 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (game->map.tex_path[i])
		{
			free(game->map.tex_path[i]);
			game->map.tex_path[i] = NULL;
		}
		if (game->tex[i].img.img && game->mlx)
		{
			mlx_destroy_image(game->mlx, game->tex[i].img.img);
			game->tex[i].img.img = NULL;
		}
		i++;
	}
}

static void	free_mlx(t_game *game)
{
	if (game->screen.img && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->screen.img);
		game->screen.img = NULL;
	}
	if (game->win && game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_textures(game);
	if (game->doors)
	{
		free(game->doors);
		game->doors = NULL;
	}
	if (game->zbuffer)
	{
		free(game->zbuffer);
		game->zbuffer = NULL;
	}
	if (game->map.grid)
	{
		free_strarr(game->map.grid);
		game->map.grid = NULL;
	}
	free_mlx(game);
}

int	close_window(t_game *game)
{
	free_game(game);
	exit(0);
}
