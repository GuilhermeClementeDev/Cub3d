/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:22:48 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/09 10:08:45 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft.h"

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	int		malloc;

	int		floor_color;
	int		ceiling_color;

	char	*no_texture;	// Norte
	char	*so_texture;	// Sul
	char	*we_texture;	// Oeste
	char	*ea_texture;	// Leste
}	t_map;

typedef struct s_game
{
	t_map	map_game;

	int		player_x;
	int		player_y;
	char	player_dir; // 'N', 'S', 'E', 'W'
}	t_game;



//PARSING

//parsing.c
void	ft_parsing(int argc, char **argv, t_game *game);

//ERROR

//ft_error.c
void	ft_error(char *str, int n, t_game *game);


#endif
