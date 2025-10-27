/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:22:26 by guclemen          #+#    #+#             */
/*   Updated: 2025/10/27 16:09:37 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_render_loop(t_game *game)
{
	ft_raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, \
	game->background.img, 0, 0);
	return 0;
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
	game->background.img = mlx_new_image(game->mlx, game->screen_width, game->screen_height);
	game->background.path = mlx_get_data_addr(game->background.img, \
&game->background.width, &game->background.line_len, &game->background.height);
	mlx_loop_hook(game->mlx, ft_render_loop, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 17, 0, ft_x, game);
	mlx_loop(game->mlx);
}
