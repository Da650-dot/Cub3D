/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:16:23 by gabriede          #+#    #+#             */
/*   Updated: 2024/10/23 15:47:57 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	*memsrc;

	memsrc = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		if (memsrc[index] == (unsigned char)c)
			return ((unsigned char *)&memsrc[index]);
		index++;
	}
	return (NULL);
}
