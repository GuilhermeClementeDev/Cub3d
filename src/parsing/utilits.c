/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:46:05 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/09 18:59:44 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_map_height(char **map_start, t_game *game)
{
	int	i;

	i = 0;
	while (map_start[i])
		i++;
	game->map_game.height = i;
}

void	ft_map_width(t_game *game)
{
	int	i;
	int	max_width;
	int	tmp_width;

	i = 0;
	max_width = 0;
	while (game->map_game.map[i])
	{
		tmp_width = ft_strlen(game->map_game.map[i]);
		if (tmp_width > max_width)
			max_width = tmp_width;
		i++;
	}
	game->map_game.width = max_width;
}
