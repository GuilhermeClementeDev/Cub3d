/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_and_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:10:46 by guclemen          #+#    #+#             */
/*   Updated: 2025/10/21 19:11:10 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
