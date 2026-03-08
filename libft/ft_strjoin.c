/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:08:35 by gabriede          #+#    #+#             */
/*   Updated: 2024/10/20 11:38:38 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total;
	char	*strconcat;

	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	strconcat = (char *)ft_calloc(total, sizeof(char));
	if (strconcat == NULL)
		return (NULL);
	ft_strlcpy(strconcat, s1, ft_strlen(s1) + 1);
	ft_strlcat(strconcat, s2, total);
	return (strconcat);
}
