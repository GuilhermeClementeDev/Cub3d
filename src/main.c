/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:20:42 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/09 19:12:53 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_build_game(t_game *game)
{
	game->map_game.map = NULL;
	game->map_game.floor_color = NULL;
	game->map_game.ceiling_color = NULL;
	game->map_game.no_texture = NULL;
	game->map_game.so_texture = NULL;
	game->map_game.we_texture = NULL;
	game->map_game.ea_texture = NULL;
	game->map_game.height = 0;
	game->map_game.width = 0;
	game->map_game.map_arrived = 0;
	game->map_game.malloc = 0;
}

void	ft_print_game(t_game *game)
{
	int	i;

	i = 0;
	ft_printf("NO texture: %s\n", game->map_game.no_texture);
	ft_printf("SO texture: %s\n", game->map_game.so_texture);
	ft_printf("WE texture: %s\n", game->map_game.we_texture);
	ft_printf("EA texture: %s\n", game->map_game.ea_texture);
	ft_printf("Floor color: %s\n", game->map_game.floor_color);
	ft_printf("Ceiling color: %s\n", game->map_game.ceiling_color);
	ft_printf("Map width: %d, height: %d\n", game->map_game.width, \
game->map_game.height);
	ft_printf("Map:\n");
	while (i < game->map_game.height)
		ft_printf("%s\n", game->map_game.map[i++]);
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
	ft_error("", 0, game);
	return (0);
}
