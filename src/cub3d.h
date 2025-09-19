/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:22:48 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/18 20:39:32 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft.h"
# include <fcntl.h>

typedef struct s_position
{
	int			width;
	int			height;
	int			count;
	char		player_dir;
}	t_player;

typedef struct s_map
{
	char		**map;
	int			height;
	int			width;

	int			malloc;

	char		*floor_color;
	char		*ceiling_color;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	t_player	player;
}	t_map;

typedef struct s_game
{
	t_map		map_game;
}	t_game;

//PARSING
//parsing.c
void	ft_parsing(int argc, char **argv, t_game *game);
//read_file.c
void	ft_read_file(char *argv, t_game *game);
//utilis.c
void	ft_map_height(char **map_start, t_game *game);
void	ft_map_width(t_game *game);
void	validate_xpm_file(char **lines, const char *path, t_game *game);
//utilis2.c
char	**ft_copy_map(t_game *game);
char	**ft_split_cub3d(char const *s, char c);
//input_verify.c
void	ft_file_type_cub(char **argv, t_game *game);
int		ft_file_type_xpm(const char *config_path);
//data_verification.c
void	ft_verify_all_config(char **lines, t_game *game);
void	ft_map_validation(t_game *game);
//flood_fill.c
void	ft_check_walls(char **cp_map, t_game *game);

//ERROR
//ft_error.c
void	ft_error(char *str, int n, t_game *game);
void	ft_free_matrix(char **matrix);
void	ft_free_call(char **to_be_free, char *msg, t_game *game);

#endif
