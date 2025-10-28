#include "../cub3d.h"
#include <math.h>

static void	rotate_player(t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dirX;
	player->dirX = player->dirX * cos(rot_speed) - player->dirY * sin(rot_speed);
	player->dirY = old_dir_x * sin(rot_speed) + player->dirY * cos(rot_speed);

	old_plane_x = player->planeX;
	player->planeX = player->planeX * cos(rot_speed) - player->planeY * sin(rot_speed);
	player->planeX = old_plane_x * sin(rot_speed) + player->planeY * cos(rot_speed);
}

static void	apply_movement(t_game *game, double move_x, double move_y)
{
	t_player	*p;
	double		new_pos_x;
	double		new_pos_y;

	p = &game->map_game.player;
	new_pos_x = p->posX + move_x;
	new_pos_y = p->posY + move_y;
	
	if (game->map_game.map[(int)p->posY][(int)new_pos_x] != '1')
		p->posX = new_pos_x;
	if (game->map_game.map[(int)p->posY][(int)p->posX] != '1')
		p->posY = new_pos_y;
}

void	handle_player_movement(t_game *game)
{
	t_player	*p;
	double		move_speed;
	double		rot_speed;
	double		move_x;
	double		move_y;

	if (game->keys.w)
	{
		move_x += p->dirX * move_speed;
		move_y += p->dirY * move_speed;
	}
	if (game->keys.s)
	{
		move_x -= p->dirX * move_speed;
		move_y -= p->dirY * move_speed;
	}
	if (game->keys.d)
	{
		move_x += p->planeX * move_speed;
		move_y += p->planeY * move_speed;
	}
	if (game->keys.a)
	{
		move_x -= p->planeX * move_speed;
		move_y -= p->planeY * move_speed;
	}
	if (move_x != 0 || move_y != 0)
		apply_movement(game, move_x, move_y);
	if (game->keys.right)
		rotate_player(p, -rot_speed);
	if (game->keys.left)
		rotate_player(p, rot_speed);
}
