#include "../../includes/cub3d.h"

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	t_player	*p;

	p = &game->player;
	ray->camera_x = 2 * x / (double)game->screen_w - 1;
	ray->ray_dir_x = p->dir_x + p->plane_x * ray->camera_x;
	ray->ray_dir_y = p->dir_y + p->plane_y * ray->camera_x;
	ray->map_x = (int)p->pos_x;
	ray->map_y = (int)p->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	ray->hit = 0;
}

static void	set_step_and_sidedist(t_game *game, t_ray *ray)
{
	t_player	*p;

	p = &game->player;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (p->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - p->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (p->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - p->pos_y) * ray->delta_dist_y;
	}
}

static void	dda(t_game *game, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= game->map.rows)
			break ;
		if (ray->map_x < 0
			|| (int)ft_strlen(game->map.grid[ray->map_y]) <= ray->map_x)
			break ;
		char cell = game->map.grid[ray->map_y][ray->map_x];
		if (cell == WALL || cell == DOOR_CLOSED || cell == ' ')
			ray->hit = 1;
	}
}

static void	calc_wall(t_game *game, t_ray *ray)
{
	t_player	*p;

	p = &game->player;
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
	
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			ray->tex_num = EA;
		else
			ray->tex_num = WE;
	}
	else
	{
		if (ray->step_y > 0)
			ray->tex_num = SO;
		else
			ray->tex_num = NO;
	}
	
	if (game->map.grid[ray->map_y][ray->map_x] == DOOR_CLOSED)
		ray->tex_num = TEX_DOOR;
	
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

void	cast_ray(t_game *game, t_ray *ray, int x)
{
	init_ray(game, ray, x);
	set_step_and_sidedist(game, ray);
	dda(game, ray);
	calc_wall(game, ray);
}

void	raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	draw_floor_ceiling(game);
	x = 0;
	while (x < game->screen_w)
	{
		cast_ray(game, &ray, x);
		draw_column(game, &ray, x);
		game->zbuffer[x] = ray.perp_wall_dist;
		x++;
	}
}
