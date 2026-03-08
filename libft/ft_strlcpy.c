/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:20:24 by gabriede          #+#    #+#             */
/*   Updated: 2024/10/16 18:50:47 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	strlen;

	index = 0;
	strlen = ft_strlen(src);
	if (size == 0)
	{
		return (strlen);
	}
	while (index < size && src[index] != 0)
	{
		dst[index] = src[index];
		index++;
	}
	if (index == size)
		index--;
	dst[index] = 0;
	return (strlen);
}
