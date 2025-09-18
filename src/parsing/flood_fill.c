/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:25:01 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/18 20:56:06 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	flood_fill(char **cp_map, int y, int x, int rows)
{
	int	cols;

	if (x < 0 || y < 0 || y >= rows)
		return (0);
	cols = ft_strlen(cp_map[y]);
	if (x >= cols)
		return (0);
	if (cp_map[y][x] == '1' || cp_map[y][x] == 'F')
		return (1);
	if (cp_map[y][x] == ' ')
		return (0);
	cp_map[y][x] = 'F';
	if (!flood_fill(cp_map, y - 1, x, rows))
		return (0);
	if (!flood_fill(cp_map, y + 1, x, rows))
		return (0);
	if (!flood_fill(cp_map, y, x - 1, rows))
		return (0);
	if (!flood_fill(cp_map, y, x + 1, rows))
		return (0);
	return (1);
}

void	ft_check_walls(char **cp_map, t_game *game)
{
	int	i;
	int	k;

	i = 0;
	while (cp_map[i])
	{
		k = 0;
		while (cp_map[i][k])
		{
			if ((cp_map[i][k] == '0' || is_player(cp_map[i][k])))
			{
				if (!flood_fill(cp_map, i, k, game->map_game.height))
				{
					ft_free_matrix(cp_map);
					ft_error("Map is open.", 4, game);
				}
			}
			k++;
		}
		i++;
	}
}
