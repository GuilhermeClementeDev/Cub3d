/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_verification.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:34:36 by guclemen          #+#    #+#             */
/*   Updated: 2025/10/31 16:17:55 by ytower           ###   ########.fr       */
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

static void	set_dir(t_player *p, int position)
{
	if (position == 1)
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (position == 2)
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	else if (position == 3)
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
}

static void	ft_player(int player_x, int player_y, t_game *game)
{
	game->map_game.player.count++;
	game->map_game.player.height = player_y;
	game->map_game.player.width = player_x;
	game->map_game.player.player_dir = game->map_game.map[player_y][player_x];
	if (game->map_game.player.player_dir == 'N')
		set_dir(&game->map_game.player, 1);
	else if (game->map_game.player.player_dir == 'S')
		set_dir(&game->map_game.player, 2);
	else if (game->map_game.player.player_dir == 'E')
		set_dir(&game->map_game.player, 3);
	else if (game->map_game.player.player_dir == 'W')
	{
		game->map_game.player.dir_x = -1;
		game->map_game.player.dir_y = 0;
		game->map_game.player.plane_x = 0;
		game->map_game.player.plane_y = -0.66;
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
