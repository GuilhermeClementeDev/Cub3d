#include "../cub3d.h"

int	exit_game(t_data *data)
{
	mlx_destroy_image(data->mlx, data->screen_img.img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);

	// free other alocated memory
	// free(map)
	// ...

	exit(0);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		return (exit_game(data), 0);
	else if (keycode == KEY_W)
		data->keys.w = 1;
	else if (keycode == KEY_A)
		data->keys.a = 1;
	else if (keycode == KEY_S)
		data->keys.s = 1;
	else if (keycode == KEY_D)
		data->keys.d = 1;
	else if (keycode == KEY_LEFT)
		data->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		data->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys.w = 0;
	else if (keycode == KEY_A)
		data->keys.a = 0;
	else if (keycode == KEY_S)
		data->keys.s = 0;
	else if (keycode == KEY_D)
		data->keys.d = 0;
	else if (keycode == KEY_LEFT)
		data->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		data->keys.right = 0;
	return (0);
}
