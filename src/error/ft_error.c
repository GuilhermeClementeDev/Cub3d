/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:01:46 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/09 10:08:10 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_msg(char *str, int n)
{
	int	std;

	if (n == 0)
		std = 1;
	else
	{
		std = 2;
		ft_putstr_fd("Error :(\n", std);
	}
	if (n == 3)
		ft_putstr_fd("Memory allocation failed.\n", std);
	else
		ft_putstr_fd(str, std);
}
void	ft_error(char *str, int n, t_game *game)
{
	int	i;

	i = 0;
	ft_msg(str, n);
	if (game)
	{
		if (game->map_game.malloc == 1)
		{
			while (i < game->map_game.height)
			{
				free(game->map_game.map[i]);
				i++;
			}
			free(game->map_game.map);
		}
		free(game);
	}
	exit(n);
}
