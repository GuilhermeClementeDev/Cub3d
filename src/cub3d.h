/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:22:48 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/09 19:20:05 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft.h"
# include <fcntl.h>

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	int		malloc;

	int		map_arrived;

	char	*floor_color;
	char	*ceiling_color;

	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
}	t_map;

typedef struct s_game
{
	t_map	map_game;

	int		player_x;
	int		player_y;
	char	player_dir;
}	t_game;

//PARSING
//parsing.c
void	ft_parsing(int argc, char **argv, t_game *game);
//read_file.c
void	ft_read_file(char *argv, t_game *game);
//utilis.c
void	ft_map_height(char **map_start, t_game *game);
void	ft_map_width(t_game *game);
//input_verify
void	ft_map_type(char **argv, t_game *game);

//ERROR
//ft_error.c
void	ft_error(char *str, int n, t_game *game);
void	ft_free_matrix(char **matrix);

#endif
