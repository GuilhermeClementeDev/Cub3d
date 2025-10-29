/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_and_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:10:46 by guclemen          #+#    #+#             */
/*   Updated: 2025/10/29 18:14:24 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int can_move(t_game *game, double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;

    if (map_x < 0 || map_y < 0)
        return 0;
    if (!game->map_game.map[map_y] || !game->map_game.map[map_y][map_x])
        return 0;
    if (game->map_game.map[map_y][map_x] == '1')
        return 0;
    return 1;
}

static void	move_front_back(t_game *game, int direction)
{
    double move_vect = (direction == 119) ? 1.0 : -1.0; // w=119, s=115
    double temp_x = game->map_game.player.width + move_vect * game->map_game.player.dir_x * MOVE_SPEED;
    double temp_y = game->map_game.player.height;
    if (can_move(game, temp_x, temp_y))
        game->map_game.player.width = temp_x;
    temp_x = game->map_game.player.width;
    temp_y = game->map_game.player.height + move_vect * game->map_game.player.dir_y * MOVE_SPEED;
    if (can_move(game, temp_x, temp_y))
        game->map_game.player.height = temp_y;
}

static void	move_sides(t_game *game, int direction)
{
    double move_vect = (direction == 100) ? 1.0 : -1.0; // d=100, a=97
    double temp_x = game->map_game.player.width + move_vect * game->map_game.player.plane_x * MOVE_SPEED;
    double temp_y = game->map_game.player.height;
    if (can_move(game, temp_x, temp_y))
        game->map_game.player.width = temp_x;
    temp_x = game->map_game.player.width;
    temp_y = game->map_game.player.height + move_vect * game->map_game.player.plane_y * MOVE_SPEED;
    if (can_move(game, temp_x, temp_y))
        game->map_game.player.height = temp_y;
}

static void	rotate_pov(t_game *game, int direction)
{
    double rotate_ang = (direction == 65361) ? -ROT_SPEED : ROT_SPEED; // left=65361, right=65363
    double old_dir_x = game->map_game.player.dir_x;
    double old_plane_x = game->map_game.player.plane_x;

    game->map_game.player.dir_x = game->map_game.player.dir_x * cos(rotate_ang) - game->map_game.player.dir_y * sin(rotate_ang);
    game->map_game.player.dir_y = old_dir_x * sin(rotate_ang) + game->map_game.player.dir_y * cos(rotate_ang);
    game->map_game.player.plane_x = game->map_game.player.plane_x * cos(rotate_ang) - game->map_game.player.plane_y * sin(rotate_ang);
    game->map_game.player.plane_y = old_plane_x * sin(rotate_ang) + game->map_game.player.plane_y * cos(rotate_ang);
}

int key_press(int key, t_game *game)
{
	if (key == 119 || key == 115)
		move_front_back(game, key);
	else if (key == 97 || key == 100)
		move_sides(game, key);
	else if (key == 65361 || key == 65363)
		rotate_pov(game, key);
	else if (key == 65307)
		ft_x(game);
	return 0;
}
