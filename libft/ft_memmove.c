/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:34:46 by gabriede          #+#    #+#             */
/*   Updated: 2024/10/23 15:36:34 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*source;
	char	*destination;
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = -1;
	source = (char *)src;
	destination = (char *)dest;
	if (dest <= src)
	{
		while (++i < n)
			destination[i] = source[i];
	}
	else if (dest > src)
	{
		while (n > 0)
		{
			destination[n - 1] = source[n - 1];
			n--;
		}
	}
	return (destination);
}
