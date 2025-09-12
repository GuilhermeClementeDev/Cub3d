/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:18:30 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/12 00:19:30 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**ft_copy_map(t_game *game)
{
	int		i;
	char	**cp;

	i = 0;
	cp = malloc((game->map_game.height + 1) * sizeof(char *));
	if (!cp)
		ft_error ("", 3, game);
	while (i < game->map_game.height)
	{
		cp[i] = ft_strdup(game->map_game.map[i]);
		if (!cp[i])
		{
			while (i >= 0)
			{
				free(cp[i]);
				i--;
			}
			free(cp);
			ft_error("", 3, game);
		}
		i++;
	}
	cp[i] = NULL;
	return (cp);
}
