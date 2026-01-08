/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 05:33:39 by yfaustin          #+#    #+#             */
/*   Updated: 2026/01/08 10:28:01 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_valid_position(t_game *game, int map_x, int map_y)
{
	if (map_y >= 0 && map_y < game->map_game.height
		&& game->map_game.map[map_y] && map_x >= 0
		&& map_x < (int)ft_strlen(game->map_game.map[map_y])
		&& game->map_game.map[map_y][map_x] != '1')
		return (1);
	return (0);
}

void	update_x_position(t_game *game, double new_x, double y)
{
	if (game->map_game.map[(int)y][(int)new_x] != '1')
		game->map_game.player.width = new_x;
}

void	update_y_position(t_game *game, double x, double new_y)
{
	if (game->map_game.map[(int)new_y][(int)x] != '1')
		game->map_game.player.height = new_y;
}
