#include "../../includes/cub3d.h"

void	img_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_tex_pixel(t_img *img, int x, int y)
{
	char	*src;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= img->width)
		x = img->width - 1;
	if (y >= img->height)
		y = img->height - 1;
	src = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	return (*(int *)src);
}

void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H / 2)
	{
		x = 0;
		while (x < WIN_W)
		{
			img_put_pixel(&game->screen, x, y, game->map.ceil_color);
			x++;
		}
		y++;
	}
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			img_put_pixel(&game->screen, x, y, game->map.floor_color);
			x++;
		}
		y++;
	}
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	t_img	*tex;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;
	int		y;

	tex = &game->tex[ray->tex_num].img;
	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_H / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		color = get_tex_pixel(tex, ray->tex_x, tex_y);
		
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		img_put_pixel(&game->screen, x, y, color);
		y++;
	}
}

int	render(t_game *game)
{
	update_doors(game);
	update_enemies(game);
	update_bullets(game);
	move_player(game);
	raycasting(game);
	draw_sprites(game);
	draw_bullets(game);
	draw_minimap(game);
	update_weapon(game);
	draw_weapon(game);
	draw_hud(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->screen.img, 0, 0);
	return (0);
}
