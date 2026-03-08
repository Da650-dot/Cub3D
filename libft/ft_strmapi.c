/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:29:55 by gabriede          #+#    #+#             */
/*   Updated: 2024/10/20 15:40:34 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned char	*str;
	unsigned int	index;
	unsigned int	size;

	size = ft_strlen(s);
	str = ft_calloc(size + 1, sizeof(unsigned char));
	if (str == NULL)
		return (NULL);
	index = 0;
	while (index < size)
	{
		str[index] = f(index, s[index]);
		index++;
	}
	return ((char *)str);
}
