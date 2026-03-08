/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:25:56 by gabriede          #+#    #+#             */
/*   Updated: 2026/03/08 16:25:56 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != '\n' && line[i] != '\t'
			&& line[i] != '\r'
			&& line[i] != DOOR_CLOSED && line[i] != DOOR_OPEN)
			return (0);
		i++;
	}
	return (1);
}

static int	handle_element(t_game *game, char *trimmed, int i, int *idx)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0
		|| ft_strncmp(trimmed, "SO ", 3) == 0
		|| ft_strncmp(trimmed, "WE ", 3) == 0
		|| ft_strncmp(trimmed, "EA ", 3) == 0
		|| ft_strncmp(trimmed, "DO ", 3) == 0
		|| ft_strncmp(trimmed, "SP ", 3) == 0)
		return (parse_texture(&game->map, trimmed));
	else if (ft_strncmp(trimmed, "F ", 2) == 0
		|| ft_strncmp(trimmed, "C ", 2) == 0)
		return (parse_color(&game->map, trimmed, 0, 0));
	else if (is_map_line(trimmed) && trimmed[0] != '\0')
	{
		*idx = i;
		return (2);
	}
	return (0);
}

int	parse_elements(t_game *game, char **lines, int *idx)
{
	int		i;
	char	*trimmed;
	int		ret;

	i = 0;
	while (lines[i])
	{
		trimmed = ft_strtrim(lines[i], " \t\n\r");
		if (!trimmed)
			return (0);
		if (trimmed[0] == '\0')
		{
			free(trimmed);
			i++;
			continue ;
		}
		ret = handle_element(game, trimmed, i, idx);
		free(trimmed);
		if (ret == 0)
			return (0);
		if (ret == 2)
			return (1);
		i++;
	}
	return (0);
}

static int	check_required(t_game *game, char **lines, int map_start)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!game->map.has_tex[i])
			return (free_strarr(lines), 0);
		i++;
	}
	if (!game->map.has_floor || !game->map.has_ceil)
		return (free_strarr(lines), 0);
	if (map_start < 0)
		return (free_strarr(lines), 0);
	return (1);
}

int	parse_file(t_game *game, const char *path)
{
	char	**lines;
	int		map_start;

	lines = read_file_lines(path);
	if (!lines)
		return (0);
	map_start = -1;
	if (!parse_elements(game, lines, &map_start))
		return (free_strarr(lines), 0);
	if (!check_required(game, lines, map_start))
		return (0);
	if (!parse_map(game, lines, map_start))
		return (free_strarr(lines), 0);
	free_strarr(lines);
	return (1);
}
