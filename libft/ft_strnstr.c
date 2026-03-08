/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:34:37 by gabriede          #+#    #+#             */
/*   Updated: 2024/10/25 14:58:48 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index;

	index = 0;
	if (!(*little))
		return ((char *)big);
	while (big[index] != 0 && index < len && len > 0)
	{
		if (index + ft_strlen(little) > len)
			return (NULL);
		if (big[index] == little[0])
			if (ft_strncmp(&big[index], &little[0], ft_strlen(little)) == 0
				&& (ft_strlen(little) + index) <= len)
				return ((char *)&big[index]);
		index++;
	}
	return (NULL);
}
