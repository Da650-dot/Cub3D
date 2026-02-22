#include "../../includes/cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
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
	if (game->sprites)
	{
		free(game->sprites);
		game->sprites = NULL;
	}
	if (game->doors)
	{
		free(game->doors);
		game->doors = NULL;
	}
	if (game->gun_tex.img && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->gun_tex.img);
		game->gun_tex.img = NULL;
	}
	if (game->map.grid)
	{
		free_strarr(game->map.grid);
		game->map.grid = NULL;
	}
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

int	close_window(t_game *game)
{
	free_game(game);
	exit(0);
}
