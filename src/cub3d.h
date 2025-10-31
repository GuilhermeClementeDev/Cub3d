/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:22:48 by guclemen          #+#    #+#             */
/*   Updated: 2025/10/31 17:10:34 by yfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define MINIMAP_SIZE 250
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05
# define RED 0xFF0000
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define GREY 0x373737

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define PRESS 2
# define RELEASE 3
# define CLOSE 17

# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"
# include <fcntl.h>
# include <math.h>

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_player
{
	double			width;
	double			height;
	int				count;
	char			player_dir;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
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

typedef struct s_raycast
{
	double			ray_dir_x;
	double			ray_dir_y;
	double			camera_x;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				side;
	char			hit_char;
	int				draw_start;
	int				draw_end;
	int				wall_height;
	double			wall_x;
}	t_raycast;

typedef struct s_game
{
	t_map		map_game;
	void		*mlx;
	void		*win;
	int			screen_width;
	int			screen_height;
	int			free_path;
	t_sprite	background;
	t_sprite	minimap;
	t_raycast	ray;
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
//ft_raycasting.c
void			ft_raycasting(t_game *game);
//mlx_utils.c
void			init_raycast(t_game *g, int x);
void			ft_init_sprites(t_game *game);
void			my_mlx_pixel_put(t_sprite *sprite, int x, int y, int color);
//ft_draw.c
void			draw_raycast_column(t_game *g, int x);

//ERROR
//ft_error.c
void			ft_error(char *str, int n, t_game *game);
void			ft_free_matrix(char **matrix);
void			ft_free_call(char **to_be_free, char *msg, t_game *game);
//ft_error2.c
void			ft_error_mlx(char *msg, int n, t_game *game);
void			ft_free_sprites(int n, t_game *game);
//MOVEMENT
//movement.c
void			handle_player_movement(t_game *game);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				exit_game(t_game *game);
//ENGINE
//engine.c
int				main_loop(t_game *game);

#endif
