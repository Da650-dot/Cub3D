/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:33:37 by gabriede          #+#    #+#             */
/*   Updated: 2024/10/23 15:17:10 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	while ((s1[index] != 0 || s2[index] != 0) && index < n)
	{
		if ((unsigned char)s1[index] > (unsigned char)s2[index])
			return (1);
		else if ((unsigned char)s1[index] < (unsigned char)s2[index])
			return (-1);
		index++;
	}
	return (0);
}
