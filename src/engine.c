#include "cub3d.h"

int	main_loop(t_game *game)
{
	handle_movement(game);
	render_frame(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen_img.img, 0, 0);
	return (0);
}
