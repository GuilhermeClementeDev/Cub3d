/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:18:39 by guclemen          #+#    #+#             */
/*   Updated: 2025/10/30 19:23:50 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	calc_tex_x(t_game *g, t_sprite *tex)
{
	int	tex_x;

	tex_x = (int)(g->ray.wall_x * (double)tex->width);
	if ((g->ray.side == 0 && g->ray.ray_dir_x > 0)
		|| (g->ray.side == 1 && g->ray.ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_wall(t_game *g, int x, t_sprite *tex, int tex_x)
{
	int				y;
	unsigned int	color;
	int				tex_y;
	double			step;
	double			tex_pos;

	tex->path = mlx_get_data_addr(tex->img, \
&tex->width, &tex->line_len, &tex_y);
	step = 1.0 * tex->height / g->ray.wall_height;
	tex_pos = \
	(g->ray.draw_start - g->screen_height / 2 + g->ray.wall_height / 2) * step;
	y = g->ray.draw_start;
	while (y < g->ray.draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = \
*(unsigned int *)(tex->path + (tex_y * tex->line_len) + (tex_x * 4));
		my_mlx_pixel_put(&g->background, x, y++, color);
		tex_pos += step;
	}
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

void	draw_raycast_column(t_game *g, int x)
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
