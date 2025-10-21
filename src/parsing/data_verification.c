/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_verification.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:34:36 by guclemen          #+#    #+#             */
/*   Updated: 2025/10/20 15:09:05 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_verify_all_config(char **lines, t_game *game)
{
	if (!game->map_game.tex_no.path || !game->map_game.tex_so.path
		|| !game->map_game.tex_we.path
		|| !game->map_game.tex_ea.path
		|| !game->map_game.ceiling_color
		|| !game->map_game.floor_color)
	{
		ft_free_matrix(lines);
		ft_error("Missing or invalid configuration", 5, game);
	}
	validate_xpm_file(lines, game->map_game.tex_no.path, game);
	validate_xpm_file(lines, game->map_game.tex_so.path, game);
	validate_xpm_file(lines, game->map_game.tex_we.path, game);
	validate_xpm_file(lines, game->map_game.tex_ea.path, game);
}

static void	ft_player(int player_x, int player_y, t_game *game)
{
	game->map_game.player.count++;
	game->map_game.player.height = player_y;
	game->map_game.player.width = player_x;
	game->map_game.player.player_dir = game->map_game.map[player_y][player_x];
	if (game->map_game.player.player_dir == 'N')
	{
		game->map_game.player.dirX = 0;
		game->map_game.player.dirY = -1;
		game->map_game.player.planeX = 0.66;
		game->map_game.player.planeY = 0;
	}
	else if (game->map_game.player.player_dir == 'S')
	{
		game->map_game.player.dirX = 0;
		game->map_game.player.dirY = 1;
		game->map_game.player.planeX = -0.66;
		game->map_game.player.planeY = 0;
	}
	else if (game->map_game.player.player_dir == 'E')
	{
		game->map_game.player.dirX = 1;
		game->map_game.player.dirY = 0;
		game->map_game.player.planeX = 0;
		game->map_game.player.planeY = 0.66;
	}
	else if (game->map_game.player.player_dir == 'W')
	{
		game->map_game.player.dirX = -1;
		game->map_game.player.dirY = 0;
		game->map_game.player.planeX = 0;
		game->map_game.player.planeY = -0.66;
	}
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
			ft_error("Invalid empty line in map", 4, game);
		while (map[i][k])
		{
			if (!ft_strchr(valid_chars, map[i][k]))
				ft_error("Map contains invalid character.", 4, game);
			if (ft_strchr(player_chars, map[i][k]))
				ft_player(k, i, game);
			if (game->map_game.player.count > 1)
				ft_error("Invalid number of players.", 4, game);
			k++;
		}
		i++;
	}
}

void	ft_map_validation(t_game *game)
{
	char	**cp_map;

	game->map_game.player.count = 0;
	ft_check_chars(game->map_game.map, game->map_game.height, game);
	if (game->map_game.player.count == 0)
		ft_error("Invalid number of player", 4, game);
	cp_map = ft_copy_map(game);
	ft_check_walls(cp_map, game);
	ft_free_matrix(cp_map);
}
