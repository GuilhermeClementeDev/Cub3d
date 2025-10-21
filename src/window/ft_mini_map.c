/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 21:12:09 by guclemen          #+#    #+#             */
/*   Updated: 2025/10/21 18:49:54 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static unsigned int	get_map_pixel_color(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map_game.height
		|| x < 0 || x >= (int)ft_strlen(game->map_game.map[y]))
		return (BLACK);
	if (game->map_game.map[y][x] == '1')
		return (GREY);
	return (WHITE);
}

static unsigned int	get_map_color_at_pixel(t_game *game, int x, int y, int half)
{
	int	map_x;
	int	map_y;

	map_x = game->map_game.player.width - half / 20 + x / 20;
	map_y = game->map_game.player.height - half / 20 + y / 20;
	if ((x - half) * (x - half) + (y - half) * (y - half) <= half * half)
		return (get_map_pixel_color(game, map_x, map_y));
	return (*(unsigned int *)(game->background.path + \
	(y * game->background.line_len) + (x * (game->background.width / 8))));
}

void	draw_minimap_pixels(t_game *game)
{
	int				x;
	int				y;
	int				half;
	unsigned int	*line;

	half = MINIMAP_SIZE / 2;
	y = 0;
	while (y < MINIMAP_SIZE)
	{
		line = (unsigned int *)(game->minimap.path
				+ y * game->minimap.line_len);
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			line[x] = get_map_color_at_pixel(game, x, y, half);
			x++;
		}
		y++;
	}
}

void	draw_player_minimap(t_game *game)
{
	int				half;
	unsigned int	*line;
	int				px;
	int				py;

	half = MINIMAP_SIZE / 2;
	py = -5;
	while (py <= 5)
	{
		px = -5;
		while (px <= 5)
		{
			line = (unsigned int *)(game->minimap.path
					+ (half + py) * game->minimap.line_len);
			line[half + px] = RED;
			px++;
		}
		py++;
	}
}

void	ft_draw_minimap(t_game *game)
{
	draw_minimap_pixels(game); // opcional: se quiser o mapa estático só uma vez, retire esta linha
    draw_player_minimap(game);
    mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 0, 0);
}
