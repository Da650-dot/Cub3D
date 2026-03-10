/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:21:49 by gabriede          #+#    #+#             */
/*   Updated: 2026/03/08 16:21:49 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	calc_bullet_transform(t_game *game, t_bullet *b,
				double *tx, double *ty)
{
	double	sp_x;
	double	sp_y;
	double	inv_det;

	sp_x = b->pos_x - game->player.pos_x;
	sp_y = b->pos_y - game->player.pos_y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	*tx = inv_det * (game->player.dir_y * sp_x - game->player.dir_x * sp_y);
	*ty = inv_det * (-game->player.plane_y * sp_x
			+ game->player.plane_x * sp_y);
}

static void	render_bullet_pixels(t_game *game, int sx, int h, double ty)
{
	int	ds_y;
	int	de_y;
	int	px;
	int	py;

	ds_y = game->screen_h / 2 - h / 2;
	de_y = game->screen_h / 2 + h / 2;
	py = ds_y;
	while (py <= de_y)
	{
		px = sx - h / 2;
		while (px <= sx + h / 2)
		{
			if (px >= 0 && px < game->screen_w
				&& py >= 0 && py < game->screen_h
				&& ty < game->zbuffer[px])
				img_put_pixel(&game->screen, px, py, 0xFF00);
			px++;
		}
		py++;
	}
}

static void	draw_one_bullet(t_game *game, t_bullet *b)
{
	double	tx;
	double	ty;
	int		screen_x;
	int		h;

	calc_bullet_transform(game, b, &tx, &ty);
	if (ty <= 0.1)
		return ;
	screen_x = (int)((game->screen_w / 2) * (1.0 + tx / ty));
	h = abs((int)(game->screen_h / ty / 8));
	if (h < 4)
		h = 4;
	if (h > 30)
		h = 30;
	render_bullet_pixels(game, screen_x, h, ty);
}

void	draw_bullets(t_game *game)
{
	int	i;

	i = 0;
	while (i < BULLET_MAX)
	{
		if (game->bullets[i].active)
			draw_one_bullet(game, &game->bullets[i]);
		i++;
	}
}
