/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfaustin <yfaustin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:07:21 by yfaustin          #+#    #+#             */
/*   Updated: 2025/10/31 17:08:20 by yfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_loop(t_game *game)
{
	handle_player_movement(game);
	ft_raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
	return (0);
}
