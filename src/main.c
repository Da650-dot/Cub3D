#include "../includes/cub3d.h"

static int	check_extension(const char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(ERR_ARGS, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (!check_extension(argv[1]))
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(ERR_EXT, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	if (!parse_file(&game, argv[1]))
		error_exit(&game, ERR_MAP);
	if (!init_game(&game))
		error_exit(&game, ERR_MLX);
	if (!load_textures(&game))
		error_exit(&game, ERR_TEX);
	init_sprites(&game);
	init_doors(&game);
	load_gun_texture(&game);
	game.mouse_x = game.screen_w / 2;
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 4, 1L << 2, mouse_click, &game);
	mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
