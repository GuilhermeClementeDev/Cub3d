/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:04:13 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/19 13:15:43 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_sprites(t_game *game)
{
	game->map_game.tex_no.img = mlx_xpm_file_to_image(game->mlx,
		game->map_game.tex_no.path,
		&game->map_game.tex_no.width,
		&game->map_game.tex_no.height);
	game->map_game.tex_so.img = mlx_xpm_file_to_image(game->mlx,
		game->map_game.tex_so.path,
		&game->map_game.tex_so.width,
		&game->map_game.tex_so.height);
	game->map_game.tex_we.img = mlx_xpm_file_to_image(game->mlx,
		game->map_game.tex_we.path,
		&game->map_game.tex_we.width,
		&game->map_game.tex_we.height);
	game->map_game.tex_ea.img = mlx_xpm_file_to_image(game->mlx,
		game->map_game.tex_ea.path,
		&game->map_game.tex_ea.width,
		&game->map_game.tex_ea.height);
	if (!game->map_game.tex_no.img || !game->map_game.tex_so.img
		|| !game->map_game.tex_we.img || !game->map_game.tex_ea.img)
		ft_free_sprites(5, game);
}

void	ft_render_background(t_game *game, int width, int height)
{
	int	x;
	int	y;
	int	half_height;
	int	color_floor;
	int	color_ceiling;

	color_floor = 0x00FF00;
	color_ceiling = 0x87CEEB;

	half_height = height / 2;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (y < half_height)
				mlx_pixel_put(game->mlx, game->win, x, y, color_ceiling);
			else
				mlx_pixel_put(game->mlx, game->win, x, y, color_floor);
			x++;
		}
		y++;
	}
}

void	ft_open_mlx(t_game *game)
{
	int	screen_width = 0;
	int	screen_height = 0;

	game->mlx = mlx_init();
	if (game->mlx == NULL)
		ft_error("Error of mlx_init.", 6, game);
	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);
	screen_width *= 0.99;
	screen_height *= 0.91;
	game->win = mlx_new_window(game->mlx, screen_width, screen_height, "Cub3d");
	if (game->win == NULL)
		ft_error_mlx("Error creating a window.", 6, game);
	ft_render_background(game, screen_width, screen_height);
}

int	ft_x(t_game *game)
{
	ft_free_sprites(0, game);
	return (0);
}
