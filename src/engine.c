#include "cub3d.h"

int	main_loop(t_game *game)
{
	handle_player_movement(game);
	ft_raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, \
		game->background.img, 0, 0);
	return (0);
}
