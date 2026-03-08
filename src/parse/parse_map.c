/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:26:09 by gabriede          #+#    #+#             */
/*   Updated: 2026/03/08 16:26:09 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	parse_map(t_game *game, char **lines, int start)
{
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
	game->map.rows = count_map_rows(lines, start);
	game->map.cols = max_line_len(lines, start, game->map.rows);
	strip_newlines(lines, start, game->map.rows);
	return (parse_checkers(game, lines, start, game->map.rows));
}
