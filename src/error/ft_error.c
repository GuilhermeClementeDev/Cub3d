/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:01:46 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/19 11:17:45 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_msg(char *str, int n)
{
	int	std;

	if (n == 0)
		std = 1;
	else
	{
		std = 2;
		ft_putstr_fd("Error :(\n", std);
	}
	if (n == 3)
		ft_putstr_fd("Memory allocation failed.\n", std);
	else
	{
		ft_putstr_fd(str, std);
		ft_putstr_fd("\n", std);
	}
}

void	ft_free_configs(t_game *game)
{
	if (game->map_game.tex_no.path)
		free(game->map_game.tex_no.path);
	if (game->map_game.tex_so.path)
		free(game->map_game.tex_so.path);
	if (game->map_game.tex_ea.path)
		free(game->map_game.tex_ea.path);
	if (game->map_game.tex_we.path)
		free(game->map_game.tex_we.path);
	if (game->map_game.floor_color)
		free(game->map_game.floor_color);
	if (game->map_game.ceiling_color)
		free(game->map_game.ceiling_color);
}

void	ft_error(char *str, int n, t_game *game)
{
	int	i;

	i = 0;
	ft_msg(str, n);
	if (game)
	{
		if (game->map_game.malloc == 1)
		{
			while (i < game->map_game.height)
			{
				free(game->map_game.map[i]);
				i++;
			}
			free(game->map_game.map);
		}
		ft_free_configs(game);
		free(game);
	}
	exit(n);
}

void	ft_free_matrix(char **matrix)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (matrix[i])
		i++;
	while (k < i)
	{
		free(matrix[k]);
		k++;
	}
	free(matrix);
}

void	ft_free_call(char **to_be_free, char *msg, t_game *game)
{
	ft_free_matrix(to_be_free);
	ft_error(msg, 5, game);
}

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
