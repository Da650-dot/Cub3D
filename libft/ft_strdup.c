/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:14:46 by gabriede          #+#    #+#             */
/*   Updated: 2024/10/18 17:31:58 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		strlen;
	char	*strcpy;

	strlen = ft_strlen(s);
	strcpy = (char *)malloc((strlen + 1) * sizeof(char));
	if (strcpy == NULL)
		return (NULL);
	ft_memcpy(strcpy, s, strlen);
	strcpy[strlen] = 0;
	return (strcpy);
}
