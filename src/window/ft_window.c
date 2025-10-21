/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:22:26 by guclemen          #+#    #+#             */
/*   Updated: 2025/10/21 18:28:45 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Inicializa as texturas e sprites
static void ft_init_sprites(t_game *game)
{
    game->map_game.tex_no.img = mlx_xpm_file_to_image(game->mlx,
        game->map_game.tex_no.path, &game->map_game.tex_no.width,
        &game->map_game.tex_no.height);
    game->map_game.tex_so.img = mlx_xpm_file_to_image(game->mlx,
        game->map_game.tex_so.path, &game->map_game.tex_so.width,
        &game->map_game.tex_so.height);
    game->map_game.tex_we.img = mlx_xpm_file_to_image(game->mlx,
        game->map_game.tex_we.path, &game->map_game.tex_we.width,
        &game->map_game.tex_we.height);
    game->map_game.tex_ea.img = mlx_xpm_file_to_image(game->mlx,
        game->map_game.tex_ea.path, &game->map_game.tex_ea.width,
        &game->map_game.tex_ea.height);

    game->background.img = NULL;
    game->background.path = NULL;

    if (!game->map_game.tex_no.img || !game->map_game.tex_so.img
        || !game->map_game.tex_we.img || !game->map_game.tex_ea.img)
        ft_free_sprites(5, game);
}

// Coloca um pixel na imagem
void my_mlx_pixel_put(t_sprite *sprite, int x, int y, int color)
{
    unsigned int *dst;
    dst = (unsigned int *)(sprite->path + y * sprite->line_len);
    dst[x] = color;
}

// DDA para calcular distância da parede
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

// Desenha uma coluna do raycasting
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

// Desenha toda a cena
void raycasting_loop(t_game *game)
{
    int x;
    for (x = 0; x < game->screen_width; x++)
        draw_column(game, x);
}

// Cria a imagem de background apenas uma vez
void ft_create_background_once(t_game *game)
{
    if (game->background.img)
        return;

    game->background.img = mlx_new_image(game->mlx,
        game->screen_width, game->screen_height);
    if (!game->background.img)
        ft_error_mlx("Error creating background image.", 6, game);

    game->background.path = mlx_get_data_addr(
        game->background.img,
        &game->background.width,
        &game->background.line_len,
        &game->background.height
    );

    raycasting_loop(game);
}

// Renderiza a imagem
void ft_render_background(t_game *game)
{
    if (!game->background.img)
        ft_create_background_once(game);

    mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
}

// Inicializa o minimap apenas uma vez
void ft_init_minimap(t_game *game)
{
    game->minimap.img = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
    game->minimap.path = mlx_get_data_addr(game->minimap.img,
        &game->minimap.width, &game->minimap.line_len, &game->minimap.height);

    // Desenha o mapa estático (paredes/floor)
    draw_minimap_pixels(game);
    // Desenha o jogador
    draw_player_minimap(game);
    // Coloca na janela
    mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 10, 10);
}

// Abre o MLX e inicializa sprites
void ft_open_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        ft_error("Error initializing MLX.", 6, game);

    mlx_get_screen_size(game->mlx, &game->screen_width, &game->screen_height);
    if (game->screen_width > 1920) game->screen_width = 1920;
    game->screen_width *= 0.99;
    game->screen_height *= 0.91;

    game->win = mlx_new_window(game->mlx,
        game->screen_width, game->screen_height, "Cub3d");
    if (!game->win)
        ft_error_mlx("Error creating window.", 6, game);

    ft_init_sprites(game);
    ft_create_background_once(game);
    ft_render_background(game);
    ft_init_minimap(game); // inicializa minimap apenas uma vez
}

// Lógica de movimento do jogador
void move_player_keys(t_game *game)
{
    double old_dirX = game->map_game.player.dirX;
    double old_planeX = game->map_game.player.planeX;

    int map_width = 0;
    int map_height = 0;
    while (game->map_game.map[map_height])
        map_height++;
    if (map_height > 0)
        while (game->map_game.map[0][map_width])
            map_width++;

    int new_x, new_y;

    if (game->keys.w)
    {
        new_x = (int)(game->map_game.player.width + game->map_game.player.dirX * MOVE_SPEED);
        new_y = (int)(game->map_game.player.height + game->map_game.player.dirY * MOVE_SPEED);
        if (new_x >= 0 && new_x < map_width &&
            game->map_game.map[(int)game->map_game.player.height][new_x] != '1')
            game->map_game.player.width += game->map_game.player.dirX * MOVE_SPEED;
        if (new_y >= 0 && new_y < map_height &&
            game->map_game.map[new_y][(int)game->map_game.player.width] != '1')
            game->map_game.player.height += game->map_game.player.dirY * MOVE_SPEED;
    }

    if (game->keys.s)
    {
        new_x = (int)(game->map_game.player.width - game->map_game.player.dirX * MOVE_SPEED);
        new_y = (int)(game->map_game.player.height - game->map_game.player.dirY * MOVE_SPEED);
        if (new_x >= 0 && new_x < map_width &&
            game->map_game.map[(int)game->map_game.player.height][new_x] != '1')
            game->map_game.player.width -= game->map_game.player.dirX * MOVE_SPEED;
        if (new_y >= 0 && new_y < map_height &&
            game->map_game.map[new_y][(int)game->map_game.player.width] != '1')
            game->map_game.player.height -= game->map_game.player.dirY * MOVE_SPEED;
    }

    // Rotação esquerda
    if (game->keys.a)
    {
        game->map_game.player.dirX = old_dirX * cos(ROT_SPEED) - game->map_game.player.dirY * sin(ROT_SPEED);
        game->map_game.player.dirY = old_dirX * sin(ROT_SPEED) + game->map_game.player.dirY * cos(ROT_SPEED);
        game->map_game.player.planeX = old_planeX * cos(ROT_SPEED) - game->map_game.player.planeY * sin(ROT_SPEED);
        game->map_game.player.planeY = old_planeX * sin(ROT_SPEED) + game->map_game.player.planeY * cos(ROT_SPEED);
    }

    // Rotação direita
    if (game->keys.d)
    {
        game->map_game.player.dirX = old_dirX * cos(-ROT_SPEED) - game->map_game.player.dirY * sin(-ROT_SPEED);
        game->map_game.player.dirY = old_dirX * sin(-ROT_SPEED) + game->map_game.player.dirY * cos(-ROT_SPEED);
        game->map_game.player.planeX = old_planeX * cos(-ROT_SPEED) - game->map_game.player.planeY * sin(-ROT_SPEED);
        game->map_game.player.planeY = old_planeX * sin(-ROT_SPEED) + game->map_game.player.planeY * cos(-ROT_SPEED);
    }
}

// Loop de atualização por frame
int update(void *param)
{
    t_game *game = (t_game *)param;

    // Atualiza posição se teclas pressionadas
    if (game->keys.w || game->keys.s || game->keys.a || game->keys.d ||
        game->keys.left || game->keys.right)
    {
        move_player_keys(game);
        raycasting_loop(game);
    }

    ft_render_background(game);
    ft_draw_minimap(game); // apenas atualiza jogador

    return 0;
}

// Eventos de teclado
int key_press(int key, t_game *game)
{
    if (key == 119) game->keys.w = 1;
    if (key == 115) game->keys.s = 1;
    if (key == 97)  game->keys.a = 1;
    if (key == 100) game->keys.d = 1;
    if (key == 65361) game->keys.left = 1;
    if (key == 65363) game->keys.right = 1;
    return 0;
}

int key_release(int key, t_game *game)
{
    if (key == 119) game->keys.w = 0;
    if (key == 115) game->keys.s = 0;
    if (key == 97)  game->keys.a = 0;
    if (key == 100) game->keys.d = 0;
    if (key == 65361) game->keys.left = 0;
    if (key == 65363) game->keys.right = 0;
    return 0;
}

// Sair
int ft_x(t_game *game)
{
    ft_free_sprites(0, game);
    exit(0);
    return 0;
}
