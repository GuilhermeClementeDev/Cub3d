/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:01:31 by guclemen          #+#    #+#             */
/*   Updated: 2025/10/28 11:35:49 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_sprites(t_game *game)
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
	game->minimap.img = NULL;
	game->minimap.path = NULL;
	if (!game->map_game.tex_no.img || !game->map_game.tex_so.img
		|| !game->map_game.tex_we.img || !game->map_game.tex_ea.img)
		ft_free_sprites(5, game);
}

void	my_mlx_pixel_put(t_sprite *sprite, int x, int y, int color)
{
	unsigned int	*dst;

	dst = (unsigned int *)(sprite->path + y * sprite->line_len);
	dst[x] = color;
}

void	init_raycast(t_game *g, int x)
{
	g->ray.camera_x = 2 * x / (double)g->screen_width - 1;
	g->ray.ray_dir_x = g->map_game.player.dir_x + \
	g->map_game.player.plane_x * g->ray.camera_x;
	g->ray.ray_dir_y = g->map_game.player.dir_y + \
	g->map_game.player.plane_y * g->ray.camera_x;
	g->ray.map_x = (int)g->map_game.player.width;
	g->ray.map_y = (int)g->map_game.player.height;
	g->ray.delta_dist_x = fabs(1 / g->ray.ray_dir_x);
	g->ray.delta_dist_y = fabs(1 / g->ray.ray_dir_y);
}
