/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:35:05 by gabriede          #+#    #+#             */
/*   Updated: 2024/10/25 15:09:19 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	index;

	index = 0;
	while (s[index] != 0)
	{
		if ((unsigned char)s[index] == (unsigned char)c)
			return ((char *)&s[index]);
		index++;
	}
	if ((unsigned char)s[index] == (unsigned char)c)
		return ((char *)&s[index]);
	return (NULL);
}
