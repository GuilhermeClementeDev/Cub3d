/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:18:30 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/15 10:35:44 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**ft_copy_map(t_game *game)
{
	int		i;
	char	**cp;

	i = 0;
	cp = malloc((game->map_game.height + 1) * sizeof(char *));
	if (!cp)
		ft_error ("", 3, game);
	while (i < game->map_game.height)
	{
		cp[i] = ft_strdup(game->map_game.map[i]);
		if (!cp[i])
		{
			while (i >= 0)
			{
				free(cp[i]);
				i--;
			}
			free(cp);
			ft_error("", 3, game);
		}
		i++;
	}
	cp[i] = NULL;
	return (cp);
}

void	validate_xpm_file(char **lines, const char *path, t_game *game)
{
	int		fd;
	char	*xpm_line;

	if (ft_file_type_xpm(path))
		ft_free_call(lines, "Invalid config file termination, must end with '.xpm'.\n"\
, game);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_free_call(lines, "Texture file does not exist or cannot be opened.\n"\
, game);
	xpm_line = get_next_line(fd);
	if (!xpm_line)
	{
		close(fd);
		ft_free_call(lines, "Texture file is empty.\n", game);
	}
	if (!ft_strnstr(xpm_line, "/* XPM */", ft_strlen(xpm_line))
		&& !ft_strnstr(xpm_line, "/* XPM2 */", ft_strlen(xpm_line)))
	{
		free(xpm_line);
		close(fd);
		ft_free_call(lines, "Texture file is not a valid XPM.\n", game);
	}
	free(xpm_line);
	close(fd);
}
