/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:22:26 by guclemen          #+#    #+#             */
/*   Updated: 2025/10/21 19:36:38 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_create_background_once(t_game *game)
{
	if (game->background.img)
		return ;
	game->background.img = mlx_new_image(game->mlx, game->screen_width, \
game->screen_height);
	if (!game->background.img)
		ft_error_mlx("Error creating background image.", 6, game);
	game->background.path = mlx_get_data_addr(game->background.img, \
&game->background.width, &game->background.line_len, &game->background.height);
	raycasting_loop(game);
}

void	ft_render_background(t_game *game)
{
	if (!game->background.img)
		ft_create_background_once(game);
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
}

void	ft_open_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error("Error initializing MLX.", 6, game);
	mlx_get_screen_size(game->mlx, &game->screen_width, &game->screen_height);
	if (game->screen_width > 1920)
		game->screen_width = 1920;
	game->screen_width *= 0.99;
	game->screen_height *= 0.91;
	game->win = mlx_new_window(game->mlx, \
game->screen_width, game->screen_height, "Cub3d");
	if (!game->win)
		ft_error_mlx("Error creating window.", 6, game);
	ft_init_sprites(game);
	ft_render_background(game);
	ft_draw_minimap(game);
}
