/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:07:21 by yfaustin          #+#    #+#             */
/*   Updated: 2026/01/08 09:54:41 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_loop(t_game *game)
{
	handle_player_movement(game);
	ft_raycasting(game);
	ft_draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
	return (0);
}
