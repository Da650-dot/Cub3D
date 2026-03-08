/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:09:30 by gabriede          #+#    #+#             */
/*   Updated: 2024/10/16 17:49:10 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int				index;
	unsigned char	*string;

	string = (unsigned char *)s;
	index = 0;
	while (n > 0)
	{
		string[index] = c;
		index++;
		n--;
	}
	return (s);
}
