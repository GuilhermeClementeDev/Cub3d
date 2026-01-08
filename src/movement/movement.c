/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:12:08 by yfaustin          #+#    #+#             */
/*   Updated: 2026/01/08 10:30:41 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

static void	rotate_player(t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y
		* sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y
		* sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y
		* cos(rot_speed);
}

static void	apply_movement(t_game *game, double move_x, double move_y)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = &game->map_game.player;
	new_x = p->width + move_x;
	new_y = p->height + move_y;
	update_x_position(game, new_x, p->height);
	update_y_position(game, p->width, new_y);
}

static void	calculate_movement(t_game *game, double move_speed,
		double *move_x, double *move_y)
{
	t_player	*p;

	p = &game->map_game.player;
	*move_x = 0;
	*move_y = 0;
	if (game->keys.w)
	{
		*move_x += p->dir_x * move_speed;
		*move_y += p->dir_y * move_speed;
	}
	if (game->keys.s)
	{
		*move_x -= p->dir_x * move_speed;
		*move_y -= p->dir_y * move_speed;
	}
	if (game->keys.d)
	{
		*move_x += p->plane_x * move_speed;
		*move_y += p->plane_y * move_speed;
	}
	if (game->keys.a)
	{
		*move_x -= p->plane_x * move_speed;
		*move_y -= p->plane_y * move_speed;
	}
}

void	handle_player_movement(t_game *game)
{
	t_player	*p;
	double		move_speed;
	double		rot_speed;
	double		move_x;
	double		move_y;

	p = &game->map_game.player;
	move_speed = MOVE_SPEED;
	rot_speed = ROT_SPEED;
	calculate_movement(game, move_speed, &move_x, &move_y);
	if (move_x != 0 || move_y != 0)
		apply_movement(game, move_x, move_y);
	if (game->keys.right)
		rotate_player(p, rot_speed);
	if (game->keys.left)
		rotate_player(p, -rot_speed);
}
