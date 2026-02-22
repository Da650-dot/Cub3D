#include "../../includes/cub3d.h"

static void	mm_draw_rect(t_game *game, int mx, int my, int color)
{
	int	px;
	int	py;
	int	sx;
	int	sy;

	sx = MM_OFFSET_X + mx * MM_SCALE;
	sy = MM_OFFSET_Y + my * MM_SCALE;
	py = sy;
	while (py < sy + MM_SCALE && py < WIN_H)
	{
		px = sx;
		while (px < sx + MM_SCALE && px < WIN_W)
		{
			img_put_pixel(&game->screen, px, py, color);
			px++;
		}
		py++;
	}
}

static void	mm_draw_player(t_game *game)
{
	int		cx;
	int		cy;
	int		dx;
	int		dy;
	int		i;

	cx = MM_OFFSET_X + (int)(game->player.pos_x * MM_SCALE);
	cy = MM_OFFSET_Y + (int)(game->player.pos_y * MM_SCALE);
	
	i = -2;
	while (i <= 2)
	{
		int j = -2;
		while (j <= 2)
		{
			img_put_pixel(&game->screen, cx + i, cy + j, MM_PLAYER);
			j++;
		}
		i++;
	}
	
	i = 1;
	while (i <= MM_SCALE * 3)
	{
		dx = cx + (int)(game->player.dir_x * i);
		dy = cy + (int)(game->player.dir_y * i);
		img_put_pixel(&game->screen, dx, dy, MM_PLAYER);
		i++;
	}
}

static int	mm_cell_color(t_game *game, int x, int y)
{
	char	c;
	int		i;

	if (y < 0 || y >= game->map.rows)
		return (MM_WALL_CLR);
	if (x < 0 || x >= (int)ft_strlen(game->map.grid[y]))
		return (MM_WALL_CLR);
	c = game->map.grid[y][x];
	if (c == WALL)
		return (MM_WALL_CLR);
	if (c == DOOR_CLOSED)
		return (MM_DOOR_CLR);
	if (c == DOOR_OPEN)
		return (MM_DOOR_CLR);
	
	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sprites[i].state != ENEMY_DEAD
			&& (int)game->sprites[i].pos_x == x
			&& (int)game->sprites[i].pos_y == y)
			return (MM_SPRITE_CL);
		i++;
	}
	return (MM_FLOOR_CLR);
}

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.cols)
		{
			mm_draw_rect(game, x, y, mm_cell_color(game, x, y));
			x++;
		}
		y++;
	}
	mm_draw_player(game);
}
