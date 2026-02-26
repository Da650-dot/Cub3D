/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/02/20 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*extract_line(char **stash)
{
	char	*newline;
	char	*line;
	char	*remaining;

	newline = ft_strchr(*stash, '\n');
	if (newline)
	{
		line = ft_substr(*stash, 0, (size_t)(newline - *stash + 1));
		remaining = ft_strdup(newline + 1);
		free(*stash);
		if (remaining && remaining[0])
			*stash = remaining;
		else
		{
			free(remaining);
			*stash = NULL;
		}
	}
	else
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
	}
	return (line);
}

static char	*append_to_stash(char *stash, char *buf, ssize_t bytes_read)
{
	char	*tmp;
	char	*segment;

	segment = ft_substr(buf, 0, (size_t)bytes_read);
	if (!segment)
	{
		free(stash);
		return (NULL);
	}
	if (!stash)
	{
		stash = segment;
	}
	else
	{
		tmp = ft_strjoin(stash, segment);
		free(stash);
		free(segment);
		stash = tmp;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		buf[BUFFER_SIZE + 1];
	ssize_t		bytes_read;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	while (!stash[fd] || !ft_strchr(stash[fd], '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buf[bytes_read] = '\0';
		stash[fd] = append_to_stash(stash[fd], buf, bytes_read);
		if (!stash[fd])
			return (NULL);
	}
	if (!stash[fd] || (!ft_strchr(stash[fd], '\n') && bytes_read <= 0
			&& stash[fd][0] == '\0'))
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	if (bytes_read < 0)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	return (extract_line(&stash[fd]));
}
