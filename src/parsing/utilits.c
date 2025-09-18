/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:46:05 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/18 12:57:38 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_map_height(char **map_start, t_game *game)
{
	int	i;
	int	last_line;

	last_line = -1;
	i = 0;
	while (map_start[i])
	{
		if (map_start[i][0] != '\0')
			last_line = i;
		i++;
	}
	game->map_game.height = last_line + 1;
}

void	ft_map_width(t_game *game)
{
	int	i;
	int	max_width;
	int	tmp_width;

	i = 0;
	max_width = 0;
	while (game->map_game.map[i])
	{
		tmp_width = ft_strlen(game->map_game.map[i]);
		if (tmp_width > max_width)
			max_width = tmp_width;
		i++;
	}
	game->map_game.width = max_width;
}

void	validate_xpm_file(char **lines, const char *path, t_game *game)
{
	int		fd;
	char	*xpm_line;

	if (ft_file_type_xpm(path))
		ft_free_call(lines, \
"Invalid config file termination, must end with '.xpm'.", game);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_free_call(lines, "Texture file does not exist or cannot be opened."\
, game);
	xpm_line = get_next_line(fd);
	if (!xpm_line)
	{
		close(fd);
		ft_free_call(lines, "Texture file is empty.", game);
	}
	if (!ft_strnstr(xpm_line, "/* XPM */", ft_strlen(xpm_line))
		&& !ft_strnstr(xpm_line, "/* XPM2 */", ft_strlen(xpm_line)))
	{
		free(xpm_line);
		close(fd);
		ft_free_call(lines, "Texture file is not a valid XPM.", game);
	}
	free(xpm_line);
	close(fd);
}
