/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 18:24:59 by gabriede          #+#    #+#             */
/*   Updated: 2026/03/08 18:24:59 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	dda_check(t_game *game, t_ray *ray)
{
	char	cell;

	if (ray->map_y < 0 || ray->map_y >= game->map.rows)
		return (-1);
	if (ray->map_x < 0
		|| (int)ft_strlen(game->map.grid[ray->map_y]) <= ray->map_x)
		return (-1);
	cell = game->map.grid[ray->map_y][ray->map_x];
	if (cell == WALL || cell == DOOR_CLOSED || cell == ' ')
		return (1);
	return (0);
}

static void	calc_tex(t_game *game, t_ray *ray)
{
	t_player	*p;

	p = &game->player;
	if (ray->side == 0)
		ray->wall_x = p->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = p->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x
			* (double)game->tex[ray->tex_num].img.width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = game->tex[ray->tex_num].img.width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = game->tex[ray->tex_num].img.width - ray->tex_x - 1;
}

void	calc_wall(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(game->screen_h / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + game->screen_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->screen_h / 2;
	if (ray->draw_end >= game->screen_h)
		ray->draw_end = game->screen_h - 1;
	if (ray->side == 0 && ray->step_x > 0)
		ray->tex_num = EA;
	else if (ray->side == 0)
		ray->tex_num = WE;
	else if (ray->step_y > 0)
		ray->tex_num = SO;
	else
		ray->tex_num = NO;
	if (game->map.grid[ray->map_y][ray->map_x] == DOOR_CLOSED)
		ray->tex_num = TEX_DOOR;
	calc_tex(game, ray);
}
