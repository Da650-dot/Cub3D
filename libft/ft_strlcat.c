/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:53:16 by gabriede          #+#    #+#             */
/*   Updated: 2024/10/18 18:47:08 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	dstlen;

	dstlen = ft_strlen(dst);
	index = 0;
	if (dstlen >= size)
		return (ft_strlen(src) + size);
	while (dstlen < (size - 1) && src[index] != 0)
	{
		dst[dstlen] = src[index];
		index++;
		dstlen++;
	}
	dst[dstlen] = 0;
	if (src[index] != 0)
		return ((dstlen - index) + ft_strlen(src));
	return (ft_strlen(dst));
}
