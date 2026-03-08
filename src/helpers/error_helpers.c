/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:41:09 by gabriede          #+#    #+#             */
/*   Updated: 2026/03/08 18:42:56 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	error_exit(t_game *game, const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
	{
		ft_putstr_fd((char *)msg, 2);
		ft_putstr_fd("\n", 2);
	}
	if (game)
		free_game(game);
	exit(1);
}
