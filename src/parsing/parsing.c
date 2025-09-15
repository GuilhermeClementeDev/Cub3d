/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:34:53 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/15 09:54:18 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_parsing(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		ft_error("Invalid number of inputs\n", 1, game);
	ft_file_type_cub(argv, game);
	ft_read_file(argv[1], game);
	ft_map_validation(game);
}
