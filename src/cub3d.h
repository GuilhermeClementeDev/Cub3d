/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:22:48 by guclemen          #+#    #+#             */
/*   Updated: 2025/10/21 19:17:12 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define MINIMAP_SIZE 250
# define MOVE_SPEED 0.15
# define ROT_SPEED 25
# define RED 0xFF0000
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define GREY 0x373737

# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"
# include <fcntl.h>
# include <math.h>

typedef struct s_keys
{
	int w;
	int a;
	int s;
	int d;
	int left;
	int right;
}	t_keys;

typedef struct s_player
{
	double			width;
	double			height;
	int				count;
	char			player_dir;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
}	t_player;

typedef struct s_sprite
{
	void	*img;
	char	*path;
	int		width;
	int		height;
	int		line_len;
}	t_sprite;

typedef struct s_map
{
	char			**map;
	int				height;

	int				malloc;

	unsigned int	floor_color;
	unsigned int	ceiling_color;

	t_sprite		tex_no;
	t_sprite		tex_so;
	t_sprite		tex_we;
	t_sprite		tex_ea;

	t_player		player;
}	t_map;

typedef struct s_color
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_game
{
	t_map		map_game;
	void		*mlx;
	void		*win;
	int			screen_width;
	int			screen_height;
	t_sprite	background;
	t_sprite	minimap;
	t_keys		keys;
}	t_game;


//PARSING
//parsing.c
void			ft_parsing(int argc, char **argv, t_game *game);
//read_file.c
void			ft_read_file(char *argv, t_game *game);
//utilis.c
void			ft_map_height(char **map_start, t_game *game);
void			validate_xpm_file(char **lines, const char *path, t_game *game);
//utilis2.c
char			**ft_copy_map(t_game *game);
char			**ft_split_cub3d(char const *s, char c);
//input_verify.c
void			ft_file_type_cub(char **argv, t_game *game);
int				ft_file_type_xpm(const char *config_path);
//data_verification.c
void			ft_verify_all_config(char **lines, t_game *game);
void			ft_map_validation(t_game *game);
//flood_fill.c
void			ft_check_walls(char **cp_map, t_game *game);
//rgb.c
unsigned int	create_trgb(char *str);

//WINDOW
//window.c
void			ft_open_mlx(t_game *game);
int				ft_x(t_game *game);
//ft_mini_map.c
void			ft_draw_minimap(t_game *game);

//ERROR
//ft_error.c
void			ft_error(char *str, int n, t_game *game);
void			ft_free_matrix(char **matrix);
void			ft_free_call(char **to_be_free, char *msg, t_game *game);
//ft_error2.c
void			ft_error_mlx(char *msg, int n, t_game *game);
void			ft_free_sprites(int n, t_game *game);

int key_release(int key, t_game *game);
int key_press(int key, t_game *game);
int update(void *param);
void draw_minimap_pixels(t_game *game);
void draw_player_minimap(t_game *game);
void raycasting_loop(t_game *game);
void ft_init_sprites(t_game *game);
void my_mlx_pixel_put(t_sprite *sprite, int x, int y, int color);
void ft_render_background(t_game *game);

#endif
