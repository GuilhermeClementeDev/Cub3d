/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfaustin <yfaustin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 05:33:39 by yfaustin          #+#    #+#             */
/*   Updated: 2025/11/08 05:34:58 by yfaustin         ###   ########.fr       */
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

void	update_x_position(t_game *game, double new_pos_x, double new_pos_y)
{
	t_player	*p;
	int			new_map_x;
	int			new_map_y;

	p = &game->map_game.player;
	new_map_y = (int)new_pos_y;
	new_map_x = (int)new_pos_x;
	if (is_valid_position(game, new_map_x, new_map_y))
		p->width = new_pos_x;
}

void	update_y_position(t_game *game, double new_pos_y)
{
	t_player	*p;
	int			new_map_x;
	int			new_map_y;

	p = &game->map_game.player;
	new_map_x = (int)p->width;
	new_map_y = (int)new_pos_y;
	if (is_valid_position(game, new_map_x, new_map_y))
		p->height = new_pos_y;
}
