/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:34:16 by guclemen          #+#    #+#             */
/*   Updated: 2025/12/05 11:06:01 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	set_draw_points(t_game *g)
{
	if (g->ray.side == 0)
		g->ray.perp_wall_dist = g->ray.side_dist_x - g->ray.delta_dist_x;
	else
		g->ray.perp_wall_dist = g->ray.side_dist_y - g->ray.delta_dist_y;
	g->ray.wall_height = (int)(g->screen_height / g->ray.perp_wall_dist);
	g->ray.draw_start = (-g->ray.wall_height / 2) + (g->screen_height / 2);
	if (g->ray.draw_start < 0)
		g->ray.draw_start = 0;
	g->ray.draw_end = (g->ray.wall_height / 2) + (g->screen_height / 2);
	if (g->ray.draw_end >= g->screen_height)
		g->ray.draw_end = g->screen_height - 1;
}

static void	wall_check(t_game *g)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (g->ray.side_dist_x < g->ray.side_dist_y)
		{
			g->ray.side_dist_x += g->ray.delta_dist_x;
			g->ray.map_x += g->ray.step_x;
			g->ray.side = 0;
		}
		else
		{
			g->ray.side_dist_y += g->ray.delta_dist_y;
			g->ray.map_y += g->ray.step_y;
			g->ray.side = 1;
		}
		if (g->map_game.map[g->ray.map_y][g->ray.map_x] == '1')
			hit = 1;
	}
}

static void	calculate_step_and_distance(t_game *g)
{
	if (g->ray.ray_dir_x < 0)
	{
		g->ray.step_x = -1;
		g->ray.side_dist_x = (g->map_game.player.width - \
g->ray.map_x) * g->ray.delta_dist_x;
	}
	else
	{
		g->ray.step_x = 1;
		g->ray.side_dist_x = (g->ray.map_x + 1.0 - \
g->map_game.player.width) * g->ray.delta_dist_x;
	}
	if (g->ray.ray_dir_y < 0)
	{
		g->ray.step_y = -1;
		g->ray.side_dist_y = (g->map_game.player.height - \
g->ray.map_y) * g->ray.delta_dist_y;
	}
	else
	{
		g->ray.step_y = 1;
		g->ray.side_dist_y = (g->ray.map_y + 1.0 - \
g->map_game.player.height) * g->ray.delta_dist_y;
	}
}

static void	calculate_wall_x(t_game *g)
{
	if (g->ray.side == 0)
		g->ray.wall_x = \
g->map_game.player.height + g->ray.perp_wall_dist * g->ray.ray_dir_y;
	else
		g->ray.wall_x = \
g->map_game.player.width + g->ray.perp_wall_dist * g->ray.ray_dir_x;
	g->ray.wall_x -= floor(g->ray.wall_x);
}

void	ft_raycasting(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->screen_width)
	{
		init_raycast(game, x);
		calculate_step_and_distance(game);
		wall_check(game);
		set_draw_points(game);
		calculate_wall_x(game);
		draw_raycast_column(game, x);
		x++;
	}
}
