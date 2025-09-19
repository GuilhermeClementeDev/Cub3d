/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:09:32 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/19 20:09:46 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error_mlx(char *msg, int n, t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	ft_error(msg, n, game);
}

void	ft_free_sprites(int n, t_game *game)
{
	if (game->background.img)
		mlx_destroy_image(game->mlx, game->background.img);
	if (game->map_game.tex_no.img)
		mlx_destroy_image(game->mlx, game->map_game.tex_no.img);
	if (game->map_game.tex_so.img)
		mlx_destroy_image(game->mlx, game->map_game.tex_so.img);
	if (game->map_game.tex_we.img)
		mlx_destroy_image(game->mlx, game->map_game.tex_we.img);
	if (game->map_game.tex_ea.img)
		mlx_destroy_image(game->mlx, game->map_game.tex_ea.img);
	if (n != 0)
		ft_error_mlx("Failed to generate image from xpm", n, game);
	else
		ft_error_mlx("Closing game...", n, game);
}
