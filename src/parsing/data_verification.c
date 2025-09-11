/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_verification.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:34:36 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/11 17:53:08 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_verify_all_config(char **lines, t_game *game)
{
	if (!game->map_game.no_texture || !game->map_game.so_texture
		|| !game->map_game.we_texture
		|| !game->map_game.ea_texture
		|| !game->map_game.ceiling_color
		|| !game->map_game.floor_color)
	{
		ft_free_matrix(lines);
		ft_error("Missing or invalid configuration\n", 4, game);
	}
}
