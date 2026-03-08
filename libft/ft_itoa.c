/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:22:54 by gabriede          #+#    #+#             */
/*   Updated: 2024/10/23 16:29:42 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inttochar(int *n, int counter)
{
	int	c;
	int	temp;

	temp = *n;
	if (*n < 0)
	{
		*n *= (-1);
		return (45);
	}
	while (counter > 0)
	{
		c = temp % 10;
		temp = temp / 10;
		counter--;
	}
	return (c + 48);
}

static int	ft_counter(int n)
{
	int	counter;

	counter = 0;
	if (n < 0)
	{
		counter = 1;
		n *= (-1);
	}
	while (n > 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		counter;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	counter = ft_counter(n);
	s = (char *)ft_calloc(counter + 1, sizeof(char));
	if (s == NULL)
		return (NULL);
	i = 0;
	while (counter > 0)
	{
		s[i] = ft_inttochar(&n, counter);
		counter--;
		i++;
	}
	s[i] = 0;
	return (s);
}
