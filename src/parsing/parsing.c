/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:34:53 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/04 19:16:13 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_map_type(char **argv)
{
	int	position;

	position = ft_strlen(argv[1]) - 4;
	if (position >= 0)
		if (!ft_strcmp(argv[position], ".cub"))
			return ;
	ft_simple_error("Invalid termination, must end with '.cub'\n" ,1);
}

void	ft_parsing(int argc, char **argv)
{
	if (argc != 2)
		ft_simple_error("Invalid number of inputs\n", 1);
	ft_map_type(argv);
}
