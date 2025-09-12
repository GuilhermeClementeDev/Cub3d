/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_verification.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:34:36 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/12 00:18:10 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_verify_all_config(char **lines, t_game *game)
{
	if (!game->map_game.no_texture || !game->map_game.so_texture
		|| !game->map_game.we_texture
		|| !game->map_game.ea_texture
		|| !game->map_game.ceiling_color
		|| !game->map_game.floor_color)
	{
		ft_free_matrix(lines);
		ft_error("Missing or invalid configuration\n", 4, game);
	}
}

static void	ft_player(int player_x, int player_y, t_game *game)
{
	game->map_game.player.count++;
	game->map_game.player.height = player_y;
	game->map_game.player.width = player_x;
}

static void	ft_check_chars(char **map, int height, t_game *game)
{
	int			i;
	int			k;
	const char	*valid_chars = "10NSEW ";
	const char	*player_chars = "NSEW";

	i = 0;
	while (i < height)
	{
		k = 0;
		if (!map[i][k])
			ft_error("Invalid empty line in map\n", 4, game);
		while (map[i][k])
		{
			if (!ft_strchr(valid_chars, map[i][k]))
				ft_error("Map contains invalid character.\n", 4, game);
			if (ft_strchr(player_chars, map[i][k]))
				ft_player(k, i, game);
			if (game->map_game.player.count > 1)
				ft_error("Invalid number of players.\n", 4, game);
			k++;
		}
		i++;
	}
}

static void	flood_fill(char **cp_map, int x, int y, t_game *game)
{
	if (y < 0 || !cp_map[y])
		ft_error("Map is open 'y'\n", 4, game);
	if (x < 0 || x >= (int)ft_strlen(cp_map[y]))
		ft_error("Map is open 'x'\n", 4, game);
	if (cp_map[y][x] == ' ')
		ft_error("Map has a blank spot", 4, game);
	if (cp_map[y][x] == '1' || cp_map[y][x] == 'F')
		return ;
	cp_map[y][x] = 'F';
	flood_fill(cp_map, x + 1, y, game);
	flood_fill(cp_map, x - 1, y, game);
	flood_fill(cp_map, x, y + 1, game);
	flood_fill(cp_map, x, y - 1, game);
}

void	ft_map_validation(t_game *game)
{
	char	**cp_map;

	game->map_game.player.count = 0;
	ft_check_chars(game->map_game.map, game->map_game.height, game);
	if (game->map_game.player.count == 0)
		ft_error("Invalid number of player\n", 4, game);
	cp_map = ft_copy_map(game);
	flood_fill(cp_map, game->map_game.player.width, \
game->map_game.player.height, game);
	ft_free_matrix(cp_map);
}
