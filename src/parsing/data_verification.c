/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_verification.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:34:36 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/11 19:25:16 by guclemen         ###   ########.fr       */
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
static void	ft_check_walls(char **map, int height, t_game *game)
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
				game->map_game.player.count++;
			if (game->map_game.player.count > 1)
				ft_error("Invalid number of players.\n", 4, game);
			k++;
		}
		i++;
	}
}

void	ft_map_validation(t_game *game)
{
	game->map_game.player.count = 0;
	ft_check_walls(game->map_game.map, game->map_game.height, game);
}
