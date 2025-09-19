/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:46:05 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/19 20:22:24 by guclemen         ###   ########.fr       */
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

static int	validate_first_xpm_line(char *line)
{
	if (!line)
		return (0);
	if (!ft_strnstr(line, "/* XPM */", ft_strlen(line))
		&& !ft_strnstr(line, "/* XPM2 */", ft_strlen(line)))
		return (0);
	return (1);
}

void	validate_xpm_file(char **lines, const char *path, t_game *game)
{
	int		fd;
	char	*xpm_line;
	int		is_valid;

	if (ft_file_type_xpm(path))
		ft_free_call(lines, \
"Invalid config file termination, must end with '.xpm'.", game);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_free_call(lines, \
"Texture file does not exist or cannot be opened.", game);
	xpm_line = get_next_line(fd);
	is_valid = validate_first_xpm_line(xpm_line);
	while (xpm_line)
	{
		free(xpm_line);
		xpm_line = get_next_line(fd);
	}
	close(fd);
	if (!is_valid)
		ft_free_call(lines, "Texture file is not a valid XPM.", game);
}
