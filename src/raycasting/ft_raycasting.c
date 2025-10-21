/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:34:16 by guclemen          #+#    #+#             */
/*   Updated: 2025/10/11 16:39:19 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_calc_ray(t_game *game, int x)
{
	t_player	*p = &game->map_game.player;
	double		cameraX;

	cameraX = 2 * x / (double)game->screen_width - 1; // de -1 a 1

	game->ray_dir_x = p->dir_width + p->plane_x * cameraX;
	game->ray_dir_y = p->dir_height + p->plane_y * cameraX;

	game->mapX = (int)p->width;
	game->mapY = (int)p->height;

	game->deltaDistX = fabs(1 / game->ray_dir_x);
	game->deltaDistY = fabs(1 / game->ray_dir_y);

	game->hit = 0;
}



void ft_raycast(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->screen_width)
	{
		ft_calc_ray(game, i);
		ft_calc_step_and_side_dist(game);
		ft_perform_dda(game);
		ft_calc_wall_height(game, i);
		ft_draw_column(game, i);
		i++;
	}
}
