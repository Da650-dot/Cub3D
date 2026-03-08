/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 09:58:09 by gabriel           #+#    #+#             */
/*   Updated: 2024/10/20 11:15:55 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	size;
	int	counter;

	counter = 0;
	start = 0;
	if (ft_strlen(s1) == 0 || ft_strlen(set) == 0)
		return (ft_substr(s1, 0, ft_strlen(s1)));
	while (s1[start] != 0 && ft_strchr(set, s1[start]))
		start++;
	size = ft_strlen(s1);
	while (s1[counter] && ft_strchr(set, s1[size]))
	{
		size--;
		counter++;
	}
	return (ft_substr(&s1[start], 0, ft_strlen(&s1[start]) - counter + 1));
}
