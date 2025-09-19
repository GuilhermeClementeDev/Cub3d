/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:20:42 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/19 13:17:19 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_build_game(t_game *game)
{
	game->map_game.map = NULL;
	game->map_game.floor_color = NULL;
	game->map_game.ceiling_color = NULL;
	game->map_game.tex_no.path = NULL;
	game->map_game.tex_so.path = NULL;
	game->map_game.tex_we.path = NULL;
	game->map_game.tex_ea.path = NULL;
	game->map_game.height = 0;
	game->map_game.width = 0;
	game->map_game.malloc = 0;
}

void	ft_print_game(t_game *game)
{
	int	i;

	i = 0;
	ft_printf("NO texture: %s\n", game->map_game.tex_no.path);
	ft_printf("SO texture: %s\n", game->map_game.tex_so.path);
	ft_printf("WE texture: %s\n", game->map_game.tex_we.path);
	ft_printf("EA texture: %s\n", game->map_game.tex_ea.path);
	ft_printf("Floor color: %s\n", game->map_game.floor_color);
	ft_printf("Ceiling color: %s\n", game->map_game.ceiling_color);
	ft_printf("Map width: %d, height: %d\n", game->map_game.width, \
game->map_game.height);
	ft_printf("Map:\n");
	while (i < game->map_game.height)
		ft_printf("%s\n", game->map_game.map[i++]);
	ft_printf("Player x: %d\n", game->map_game.player.width);
	ft_printf("Player y: %d\n", game->map_game.player.height);
	ft_printf("Player y: %c\n", game->map_game.player.player_dir);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		ft_error("", 3, game);
	ft_build_game(game);
	ft_parsing(argc, argv, game);
	ft_open_mlx(game);
	mlx_hook(game->win, 17, 0, ft_x, game);
	mlx_loop(game->mlx);
	ft_print_game(game);
	ft_error("", 0, game);
	return (0);
}
