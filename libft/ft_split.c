/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/02/20 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_word(char const *s, char c, size_t *pos)
{
	size_t	start;
	size_t	len;

	while (s[*pos] == c)
		(*pos)++;
	start = *pos;
	len = 0;
	while (s[*pos] && s[*pos] != c)
	{
		len++;
		(*pos)++;
	}
	return (ft_substr(s, (unsigned int)start, len));
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	words;
	size_t	pos;
	size_t	i;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	pos = 0;
	i = 0;
	while (i < words)
	{
		result[i] = get_word(s, c, &pos);
		if (!result[i])
		{
			while (i > 0)
				free(result[--i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[words] = NULL;
	return (result);
}
