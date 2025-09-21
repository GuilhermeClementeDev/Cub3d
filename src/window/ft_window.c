/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:04:13 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/20 21:16:19 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_init_sprites(t_game *game)
{
	game->map_game.tex_no.img = mlx_xpm_file_to_image(game->mlx, \
game->map_game.tex_no.path, &game->map_game.tex_no.width, \
&game->map_game.tex_no.height);
	game->map_game.tex_so.img = mlx_xpm_file_to_image(game->mlx, \
game->map_game.tex_so.path, &game->map_game.tex_so.width, \
&game->map_game.tex_so.height);
	game->map_game.tex_we.img = mlx_xpm_file_to_image(game->mlx, \
game->map_game.tex_we.path, &game->map_game.tex_we.width, \
&game->map_game.tex_we.height);
	game->map_game.tex_ea.img = mlx_xpm_file_to_image(game->mlx, \
game->map_game.tex_ea.path, &game->map_game.tex_ea.width, \
&game->map_game.tex_ea.height);
	game->background.img = NULL;
	game->background.path = NULL;
	if (!game->map_game.tex_no.img || !game->map_game.tex_so.img
		|| !game->map_game.tex_we.img || !game->map_game.tex_ea.img)
		ft_free_sprites(5, game);
}

static void	ft_create_background(t_game *game)
{
	int				y;
	int				x;
	unsigned int	*line;

	game->background.img = mlx_new_image(game->mlx, \
game->screen_width, game->screen_height);
	game->background.path = mlx_get_data_addr(game->background.img, \
&game->background.width, &game->background.line_len, \
&game->background.height);
	y = 0;
	while (y < game->screen_height)
	{
		line = (unsigned int *)(game->background.path + y * \
game->background.line_len);
		x = 0;
		while (x < game->screen_width)
		{
			if (y < game->screen_height / 2)
				line[x] = 0x87CEEB;
			else
				line[x] = 0x00FF00;
			x++;
		}
		y++;
	}
}

void	ft_render_background(t_game *game)
{
	if (!game->background.img)
		ft_create_background(game);
	if (game->background.img)
		mlx_put_image_to_window(game->mlx,
			game->win, game->background.img, 0, 0);
}

void	ft_open_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		ft_error("Error of mlx_init.", 6, game);
	mlx_get_screen_size(game->mlx, &game->screen_width, &game->screen_height);
	game->screen_width *= 0.99;
	game->screen_height *= 0.91;
	game->win = mlx_new_window(game->mlx, \
game->screen_width, game->screen_height, "Cub3d");
	if (game->win == NULL)
		ft_error_mlx("Error creating a window.", 6, game);
	ft_init_sprites(game);
	ft_render_background(game);
	ft_draw_minimap(game);
}

int	ft_x(t_game *game)
{
	ft_free_sprites(0, game);
	return (0);
}
