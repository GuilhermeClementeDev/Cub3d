#include "../cub3d.h"
#include <math.h>

static void	rotate_player(t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y * sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);

	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y * sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y * cos(rot_speed);
}

static void	apply_movement(t_game *game, double move_x, double move_y)
{
	t_player	*p;
	double	new_pos_x;
	double	new_pos_y;
	int		new_map_x;
	int		new_map_y;

	p = &game->map_game.player;
	new_pos_x = p->width + move_x;
	new_pos_y = p->height + move_y;
	new_map_y = (int)new_pos_y;
	new_map_x = (int)new_pos_x;
	
	// Verifica colis?o apenas na nova posi??o X primeiro
	if (new_map_y >= 0 && new_map_y < game->map_game.height
		&& game->map_game.map[new_map_y]
		&& new_map_x >= 0 && new_map_x < (int)ft_strlen(game->map_game.map[new_map_y])
		&& game->map_game.map[new_map_y][new_map_x] != '1')
	{
		p->width = new_pos_x;
	}
	
	// Depois verifica na nova posi??o Y
	new_map_x = (int)p->width;
	if (new_map_y >= 0 && new_map_y < game->map_game.height
		&& game->map_game.map[new_map_y]
		&& new_map_x >= 0 && new_map_x < (int)ft_strlen(game->map_game.map[new_map_y])
		&& game->map_game.map[new_map_y][new_map_x] != '1')
	{
		p->height = new_pos_y;
	}
}

void	handle_player_movement(t_game *game)
{
	t_player	*p;
	double		move_speed;
	double		rot_speed;
	double		move_x;
	double		move_y;

	p = &game->map_game.player;
	move_speed = MOVE_SPEED;
	rot_speed = ROT_SPEED;
	move_x = 0;
	move_y = 0;

	if (game->keys.w)
	{
		move_x += p->dir_x * move_speed;
		move_y += p->dir_y * move_speed;
	}
	if (game->keys.s)
	{
		move_x -= p->dir_x * move_speed;
		move_y -= p->dir_y * move_speed;
	}
	if (game->keys.d)
	{
		move_x += p->plane_x * move_speed;
		move_y += p->plane_y * move_speed;
	}
	if (game->keys.a)
	{
		move_x -= p->plane_x * move_speed;
		move_y -= p->plane_y * move_speed;
	}
	if (move_x != 0 || move_y != 0)
		apply_movement(game, move_x, move_y);
	if (game->keys.right)
		rotate_player(p, rot_speed);
	if (game->keys.left)
		rotate_player(p, -rot_speed);
}
