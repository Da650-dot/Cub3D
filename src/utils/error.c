#include "../../includes/cub3d.h"

void	error_exit(t_game *game, const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
	{
		ft_putstr_fd((char *)msg, 2);
		ft_putstr_fd("\n", 2);
	}
	if (game)
		free_game(game);
	exit(1);
}

char	**read_file_lines(const char *path)
{
	int		fd;
	char	*line;
	char	**result;
	int		count;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		count++;
	}
	close(fd);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (close(fd), NULL);
	i = 0;
	while (i < count)
	{
		result[i] = get_next_line(fd);
		if (!result[i])
			break ;
		i++;
	}
	result[i] = NULL;
	close(fd);
	return (result);
}

void	free_strarr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	strarr_len(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}
