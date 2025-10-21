/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:34:16 by guclemen          #+#    #+#             */
/*   Updated: 2025/10/21 19:07:31 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double calculate_dda(t_game *game, double ray_dir_x, double ray_dir_y, int *side, char *hit_char)
{
    int map_x = (int)game->map_game.player.width;
    int map_y = (int)game->map_game.player.height;
    double side_dist_x, side_dist_y;
    double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
    double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
    int step_x, step_y;
    int hit = 0;

    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (game->map_game.player.width - map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - game->map_game.player.width) * delta_dist_x;
    }

    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (game->map_game.player.height - map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - game->map_game.player.height) * delta_dist_y;
    }

    while (!hit)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            *side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            *side = 1;
        }
        if (game->map_game.map[map_y][map_x] == '1' || game->map_game.map[map_y][map_x] == 'D')
        {
            *hit_char = game->map_game.map[map_y][map_x];
            hit = 1;
        }
    }

    if (*side == 0)
        return (side_dist_x - delta_dist_x);
    else
        return (side_dist_y - delta_dist_y);
}

static void draw_column(t_game *game, int x)
{
    double camera_x = 2 * x / (double)game->screen_width - 1;
    double ray_dir_x = game->map_game.player.dirX + game->map_game.player.planeX * camera_x;
    double ray_dir_y = game->map_game.player.dirY + game->map_game.player.planeY * camera_x;
    double perp_wall_dist;
    int side;
    int wall_height;
    int draw_start, draw_end;
    int y;
    char hit_char;
    t_sprite *tex;
    double wall_x;
    int tex_x, tex_y;
    double step, tex_pos;
    unsigned int color;

    perp_wall_dist = calculate_dda(game, ray_dir_x, ray_dir_y, &side, &hit_char);
    wall_height = (int)(game->screen_height / perp_wall_dist);
    draw_start = (-wall_height / 2) + (game->screen_height / 2);
    if (draw_start < 0) draw_start = 0;
    draw_end = (wall_height / 2) + (game->screen_height / 2);
    if (draw_end >= game->screen_height) draw_end = game->screen_height - 1;

    // Teto
    for (y = 0; y < draw_start; y++)
        my_mlx_pixel_put(&game->background, x, y, game->map_game.ceiling_color);

    // Escolhe textura
    if (side == 0 && ray_dir_x > 0) tex = &game->map_game.tex_ea;
    else if (side == 0 && ray_dir_x < 0) tex = &game->map_game.tex_we;
    else if (side == 1 && ray_dir_y > 0) tex = &game->map_game.tex_so;
    else tex = &game->map_game.tex_no;

    // Posição exata da parede
    if (side == 0)
        wall_x = game->map_game.player.height + perp_wall_dist * ray_dir_y;
    else
        wall_x = game->map_game.player.width + perp_wall_dist * ray_dir_x;
    wall_x -= floor(wall_x);

    tex_x = (int)(wall_x * tex->width);
    if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
        tex_x = tex->width - tex_x - 1;

    step = 1.0 * tex->height / wall_height;
    tex_pos = (draw_start - game->screen_height / 2 + wall_height / 2) * step;

    for (y = draw_start; y < draw_end; y++)
    {
        tex_y = (int)tex_pos & (tex->height - 1);
        tex_pos += step;
        color = *(unsigned int *)(tex->path + tex_y * tex->line_len + tex_x * 4);
        my_mlx_pixel_put(&game->background, x, y, color);
    }

    // Chão
    for (y = draw_end; y < game->screen_height; y++)
        my_mlx_pixel_put(&game->background, x, y, game->map_game.floor_color);
}


void raycasting_loop(t_game *game)
{
	int x;
	for (x = 0; x < game->screen_width; x++)
		draw_column(game, x);
}
