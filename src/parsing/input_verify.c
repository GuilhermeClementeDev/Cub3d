/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_verify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:42:17 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/18 10:57:16 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_file_type_cub(char **argv, t_game *game)
{
	int	position;

	position = ft_strlen(argv[1]) - 4;
	if (position >= 0)
		if (!ft_strcmp(&argv[1][position], ".cub"))
			return ;
	ft_error("Invalid termination, must end with '.cub'", 1, game);
}

int	ft_file_type_xpm(const char *config_path)
{
	int	position;

	position = ft_strlen(config_path) - 4;
	if (position >= 0)
		if (!ft_strcmp(&config_path[position], ".xpm"))
			return (0);
	return (1);
}
