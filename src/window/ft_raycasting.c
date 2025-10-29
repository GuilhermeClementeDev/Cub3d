/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:34:16 by guclemen          #+#    #+#             */
/*   Updated: 2025/10/29 18:02:30 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	set_draw_points(t_game *g)
{
	if (g->ray.side == 0)
		g->ray.perp_wall_dist = g->ray.side_dist_x - g->ray.delta_dist_x;
	else
		g->ray.perp_wall_dist = g->ray.side_dist_y - g->ray.delta_dist_y;
	g->ray.wall_height = (int)(g->screen_height / g->ray.perp_wall_dist);
	g->ray.draw_start = (-g->ray.wall_height / 2) + (g->screen_height / 2);
	if (g->ray.draw_start < 0)
		g->ray.draw_start = 0;
	g->ray.draw_end = (g->ray.wall_height / 2) + (g->screen_height / 2);
	if (g->ray.draw_end >= g->screen_height)
		g->ray.draw_end = g->screen_height - 1;
}

static void	wall_check(t_game *g)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (g->ray.side_dist_x < g->ray.side_dist_y)
		{
			g->ray.side_dist_x += g->ray.delta_dist_x;
			g->ray.map_x += g->ray.step_x;
			g->ray.side = 0;
		}
		else
		{
			g->ray.side_dist_y += g->ray.delta_dist_y;
			g->ray.map_y += g->ray.step_y;
			g->ray.side = 1;
		}
		if (g->map_game.map[g->ray.map_y][g->ray.map_x] == '1')
			hit = 1;
	}
}

static void	calculate_step_and_distance(t_game *g)
{
	if (g->ray.ray_dir_x < 0)
	{
		g->ray.step_x = -1;
		g->ray.side_dist_x = (g->map_game.player.width - \
g->ray.map_x) * g->ray.delta_dist_x;
	}
	else
	{
		g->ray.step_x = 1;
		g->ray.side_dist_x = (g->ray.map_x + 1.0 - \
g->map_game.player.width) * g->ray.delta_dist_x;
	}
	if (g->ray.ray_dir_y < 0)
	{
		g->ray.step_y = -1;
		g->ray.side_dist_y = (g->map_game.player.height - \
g->ray.map_y) * g->ray.delta_dist_y;
	}
	else
	{
		g->ray.step_y = 1;
		g->ray.side_dist_y = (g->ray.map_y + 1.0 - \
g->map_game.player.height) * g->ray.delta_dist_y;
	}
}
static void calculate_wall_x(t_game *g)
{
	if (g->ray.side == 0) // Parede vertical (Leste/Oeste), usa coord. Y
		g->ray.wall_x = g->map_game.player.height + g->ray.perp_wall_dist * g->ray.ray_dir_y;
	else // Parede horizontal (Norte/Sul), usa coord. X
		g->ray.wall_x = g->map_game.player.width + g->ray.perp_wall_dist * g->ray.ray_dir_x;
	g->ray.wall_x -= floor(g->ray.wall_x);
}

static t_sprite	*get_wall_texture(t_game *g)
{
	if (g->ray.side == 0)
	{
		if (g->ray.ray_dir_x > 0)
			return (&g->map_game.tex_we);
		else
			return (&g->map_game.tex_ea);
	}
	else
	{
		if (g->ray.ray_dir_y > 0)
			return (&g->map_game.tex_no);
		else
			return (&g->map_game.tex_so);
	}
}
static int	calc_tex_x(t_game *g, t_sprite *tex)
{
	int tex_x;

	// converte wall_x (0 a 1) para coordenada X da textura
	tex_x = (int)(g->ray.wall_x * (double)tex->width);
	if ((g->ray.side == 0 && g->ray.ray_dir_x > 0)
		|| (g->ray.side == 1 && g->ray.ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_wall(t_game *g, int x, t_sprite *tex, int tex_x)
{
	int			y;
	unsigned int	color;
	int			tex_y;
	double		step;
	double		tex_pos;

	tex->path = mlx_get_data_addr(tex->img,
		&tex->width, &tex->line_len, &tex_y);

	// passo por pixel na tela para percorrer a textura inteira
	step = 1.0 * tex->height / g->ray.wall_height;

	// posição inicial na textura considerando draw_start
	tex_pos = (g->ray.draw_start - g->screen_height / 2 + g->ray.wall_height / 2) * step;

	y = g->ray.draw_start;
	while (y < g->ray.draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= tex->height) tex_y = tex->height - 1;
		color = *(unsigned int*)(tex->path + (tex_y * tex->line_len) + (tex_x * 4)); // 4 bytes por pixel
		my_mlx_pixel_put(&g->background, x, y++, color);
		tex_pos += step;
	}
}



static void	draw_raycast_column(t_game *g, int x)
{
	int			y;
	t_sprite	*tex;
	int			tex_x;

	y = 0;
	while (y < g->ray.draw_start)
	{
		my_mlx_pixel_put(&g->background, x, y, g->map_game.ceiling_color);
		y++;
	}
	y = g->ray.draw_start;
	tex = get_wall_texture(g);
	tex_x = calc_tex_x(g, tex);
	draw_wall(g, x, tex, tex_x);
	y = g->ray.draw_end;
	while (y < g->screen_height)
	{
		my_mlx_pixel_put(&g->background, x, y, g->map_game.floor_color);
		y++;
	}
}

void	ft_raycasting(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->screen_width)
	{
		init_raycast(game, x);
		calculate_step_and_distance(game);
		wall_check(game);
		set_draw_points(game);
		calculate_wall_x(game);
		draw_raycast_column(game, x);
		x++;
	}
}
