#include "../../includes/cub3d.h"

static int	set_texture(t_map *map, int idx, char *path)
{
	if (map->has_tex[idx])
		return (0);
	map->tex_path[idx] = ft_strdup(path);
	if (!map->tex_path[idx])
		return (0);
	map->has_tex[idx] = 1;
	return (1);
}

int	parse_texture(t_map *map, char *line)
{
	char	*path;

	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		path = ft_strtrim(line + 3, " \t\n");
		if (!path || path[0] == '\0')
			return (free(path), 0);
		if (!set_texture(map, NO, path))
			return (free(path), 0);
		free(path);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		path = ft_strtrim(line + 3, " \t\n");
		if (!path || path[0] == '\0')
			return (free(path), 0);
		if (!set_texture(map, SO, path))
			return (free(path), 0);
		free(path);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		path = ft_strtrim(line + 3, " \t\n");
		if (!path || path[0] == '\0')
			return (free(path), 0);
		if (!set_texture(map, WE, path))
			return (free(path), 0);
		free(path);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		path = ft_strtrim(line + 3, " \t\n");
		if (!path || path[0] == '\0')
			return (free(path), 0);
		if (!set_texture(map, EA, path))
			return (free(path), 0);
		free(path);
	}
	else if (ft_strncmp(line, "DO ", 3) == 0)
	{
		path = ft_strtrim(line + 3, " \t\n\r");
		if (!path || path[0] == '\0')
			return (free(path), 0);
		if (!set_texture(map, TEX_DOOR, path))
			return (free(path), 0);
		free(path);
	}
	else if (ft_strncmp(line, "SP ", 3) == 0)
	{
		path = ft_strtrim(line + 3, " \t\n\r");
		if (!path || path[0] == '\0')
			return (free(path), 0);
		if (!set_texture(map, TEX_SPRITE, path))
			return (free(path), 0);
		free(path);
	}
	return (1);
}

static int	parse_rgb(char *str, int *r, int *g, int *b)
{
	char	**parts;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		free_strarr(parts);
		return (0);
	}
	*r = ft_atoi(parts[0]);
	*g = ft_atoi(parts[1]);
	*b = ft_atoi(parts[2]);
	free_strarr(parts);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (0);
	return (1);
}

int	parse_color(t_map *map, char *line)
{
	char	*rgb_str;
	int		r;
	int		g;
	int		b;

	if (line[0] == 'F')
	{
		if (map->has_floor)
			return (0);
		rgb_str = ft_strtrim(line + 2, " \t\n");
		if (!rgb_str)
			return (0);
		if (!parse_rgb(rgb_str, &r, &g, &b))
			return (free(rgb_str), 0);
		free(rgb_str);
		map->floor_color = (r << 16) | (g << 8) | b;
		map->has_floor = 1;
	}
	else if (line[0] == 'C')
	{
		if (map->has_ceil)
			return (0);
		rgb_str = ft_strtrim(line + 2, " \t\n");
		if (!rgb_str)
			return (0);
		if (!parse_rgb(rgb_str, &r, &g, &b))
			return (free(rgb_str), 0);
		free(rgb_str);
		map->ceil_color = (r << 16) | (g << 8) | b;
		map->has_ceil = 1;
	}
	return (1);
}
