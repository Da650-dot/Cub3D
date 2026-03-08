#include "../../includes/cub3d.h"

static int	count_map_rows(char **lines, int start)
{
	int		count;
	char	*trimmed;

	count = 0;
	while (lines[start + count])
		count++;
	while (count > 0)
	{
		trimmed = ft_strtrim(lines[start + count - 1], " \t\r\n");
		if (trimmed && trimmed[0] != '\0')
		{
			free(trimmed);
			break ;
		}
		free(trimmed);
		count--;
	}
	return (count);
}

static int	max_line_len(char **lines, int start, int rows)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = 0;
	while (i < rows)
	{
		len = ft_strlen(lines[start + i]);
		while (len > 0 && (lines[start + i][len - 1] == '\n'
				|| lines[start + i][len - 1] == '\r'))
			len--;
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static int	set_player_pos(t_player *p, char c, int x, int y)
{
	if (p->pos_x != -1)
		return (0);
	p->pos_x = x + 0.5;
	p->pos_y = y + 0.5;
	init_player_direction(p, c);
	return (1);
}

static int	validate_chars(t_game *game, int rows, int cols)
{
	int		x;
	int		y;
	int		player_count;
	char	c;

	player_count = 0;
	game->player.pos_x = -1;
	game->player.pos_y = -1;
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (game->map.grid[y][x])
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
			x++;
		}
		y++;
	}
	(void)cols;
	return (player_count == 1);
}

static int	is_surrounded(t_game *game)
{
	int	x;
	int	y;
	int	rows;

	rows = game->map.rows;
	y = 0;
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

static void	strip_newlines(char **lines, int start, int rows)
{
	int	i;
	int	len;

	i = 0;
	while (i < rows)
	{
		len = ft_strlen(lines[start + i]);
		if (len > 0 && lines[start + i][len - 1] == '\n')
			lines[start + i][--len] = '\0';
		if (len > 0 && lines[start + i][len - 1] == '\r')
			lines[start + i][--len] = '\0';
		i++;
	}
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

int	parse_map(t_game *game, char **lines, int start)
{
	int		rows;
	int		cols;
	int		i;
	int		r;
	int		w;

	i = start;
	while (lines[i])
	{
		r = 0;
		w = 0;
		while (lines[i][r])
		{
			if (lines[i][r] != ' ')
				lines[i][w++] = lines[i][r];
			r++;
		}
		lines[i][w] = '\0';
		i++;
	}
	rows = count_map_rows(lines, start);
	cols = max_line_len(lines, start, rows);
	game->map.rows = rows;
	game->map.cols = cols;
	strip_newlines(lines, start, rows);
	if (!build_grid(game, lines, start, cols))
		return (0);
	if (!validate_chars(game, rows, cols))
		return (0);
	if (!is_surrounded(game))
		return (0);
	return (1);
}
