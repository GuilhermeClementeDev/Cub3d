/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:20:42 by guclemen          #+#    #+#             */
/*   Updated: 2025/11/08 05:30:40 by yfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_mlx_hooks(t_game *game)
{
	mlx_hook(game->win, PRESS, 1L << 0, key_press, game);
	mlx_hook(game->win, RELEASE, 1L << 1, key_release, game);
	mlx_hook(game->win, CLOSE, 0, exit_game, game);
	mlx_loop_hook(game->mlx, main_loop, game);
}

static void	ft_build_game(t_game *game)
{
	game->map_game.map = NULL;
	game->map_game.floor_color = 0;
	game->map_game.ceiling_color = 0;
	game->map_game.tex_no.path = NULL;
	game->map_game.tex_so.path = NULL;
	game->map_game.tex_we.path = NULL;
	game->map_game.tex_ea.path = NULL;
	game->map_game.height = 0;
	game->map_game.malloc = 0;
	game->free_path = 0;
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
}

void	ft_print_game(t_game *game)
{
	int	i;

	i = 0;
	ft_printf("NO texture: %s\n", game->map_game.tex_no.path);
	ft_printf("SO texture: %s\n", game->map_game.tex_so.path);
	ft_printf("WE texture: %s\n", game->map_game.tex_we.path);
	ft_printf("EA texture: %s\n", game->map_game.tex_ea.path);
	ft_printf("Floor color: %u\n", game->map_game.floor_color);
	ft_printf("Ceiling color: %u\n", game->map_game.ceiling_color);
	ft_printf("Map height: %d\n", game->map_game.height);
	ft_printf("Map:\n");
	while (i < game->map_game.height)
		ft_printf("%s\n", game->map_game.map[i++]);
	ft_printf("Player x: %.2f\n", game->map_game.player.width);
	ft_printf("Player y: %.2f\n", game->map_game.player.height);
	ft_printf("Player dir: %c\n", game->map_game.player.player_dir);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		ft_error("", 3, game);
	ft_build_game(game);
	ft_parsing(argc, argv, game);
	ft_print_game(game);
	ft_open_mlx(game);
	init_mlx_hooks(game);
	mlx_loop(game->mlx);
	return (0);
}
