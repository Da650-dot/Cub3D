/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:15:40 by gabriede          #+#    #+#             */
/*   Updated: 2024/10/25 14:36:55 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_inttochar(int *n, int counter)
{
	int	c;
	int	temp;

	temp = *n;
	while (counter > 0)
	{
		c = temp % 10;
		temp = temp / 10;
		counter--;
	}
	c = c + 48;
	return (c);
}

static int	ft_counter(int n)
{
	int	counter;

	counter = 0;
	while (n > 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		counter;
	char	c;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n == 0)
		write(fd, "0", 1);
	else if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd((n * -1), fd);
	}
	else if (n > 0)
	{
		counter = ft_counter(n);
		while (counter > 0)
		{
			c = ft_inttochar(&n, counter);
			write(fd, &c, 1);
			counter--;
		}
	}
}
