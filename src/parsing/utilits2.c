/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:18:30 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/14 19:58:51 by guclemen         ###   ########.fr       */
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

void validate_xpm_file(char **lines, const char *path, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_free_matrix(lines);
		ft_error("Texture file does not exist or cannot be opened.\n", 4, game);
	}
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		ft_free_matrix(lines);
		ft_error("Texture file is empty.\n", 4, game);
	}
	if (!ft_strnstr(line, "/* XPM */", ft_strlen(line)) && !ft_strnstr(line, "/* XPM2 */", ft_strlen(line)))
	{
		free(line);
		ft_free_matrix(lines);
		close(fd);
		ft_error("Texture file is not a valid XPM.\n", 4, game);
	}
	free(line);
	close(fd);
}
