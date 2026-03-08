/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 17:12:42 by gabriede          #+#    #+#             */
/*   Updated: 2026/03/08 18:42:49 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	set_player_pos(t_player *p, char c, int x, int y)
{
	if (p->pos_x != -1)
		return (0);
	p->pos_x = x + 0.5;
	p->pos_y = y + 0.5;
	init_player_direction(p, c);
	return (1);
}

static int	is_surrounded(t_game *game, int x, int y, int rows)
{
	while (y < rows)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == '0'
				|| game->map.grid[y][x] == DOOR_OPEN)
			{
				if (y == 0 || y == rows - 1)
					return (0);
				if (x == 0)
					return (0);
				if (!game->map.grid[y][x - 1]
					|| !game->map.grid[y][x + 1])
					return (0);
				if (!game->map.grid[y - 1][x]
					|| !game->map.grid[y + 1][x])
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

static int	validate_chars(t_game *game, int rows, int player_count, int y)
{
	int		x;
	char	c;

	game->player.pos_x = -1;
	game->player.pos_y = -1;
	while (++y < rows)
	{
		x = -1;
		while (game->map.grid[y][++x])
		{
			c = game->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (!set_player_pos(&game->player, c, x, y))
					return (0);
				player_count++;
				game->map.grid[y][x] = '0';
			}
			else if (c != '0' && c != '1' && c != ' ' && c != '\r'
				&& c != DOOR_CLOSED && c != DOOR_OPEN)
				return (0);
		}
	}
	return (player_count == 1);
}

static int	build_grid(t_game *game, char **lines, int start, int cols)
{
	int	i;
	int	rows;

	rows = game->map.rows;
	game->map.grid = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!game->map.grid)
		return (0);
	i = 0;
	while (i < rows)
	{
		game->map.grid[i] = (char *)malloc(sizeof(char) * (cols + 1));
		if (!game->map.grid[i])
			return (0);
		ft_memset(game->map.grid[i], ' ', cols);
		game->map.grid[i][cols] = '\0';
		ft_memcpy(game->map.grid[i], lines[start + i],
			ft_strlen(lines[start + i]));
		i++;
	}
	game->map.grid[rows] = NULL;
	return (1);
}

int	parse_checkers(t_game *game, char **lines, int start, int rows)
{
	if (!build_grid(game, lines, start, game->map.cols))
		return (0);
	if (!validate_chars(game, rows, 0, -1))
		return (0);
	if (!is_surrounded(game, 0, 0, game->map.rows))
		return (0);
	return (1);
}
