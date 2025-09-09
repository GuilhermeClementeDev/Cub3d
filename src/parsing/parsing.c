/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:34:53 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/09 10:11:41 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_map_type(char **argv, t_game *game)
{
	int	position;

	position = ft_strlen(argv[1]) - 4;
	if (position >= 0)
		if (!ft_strcmp(&argv[1][position], ".cub"))
			return ;
	ft_error("Invalid termination, must end with '.cub'\n" ,1, game);
}

/*void	ft_read_file(char *argv, t_game *game)
{
	int		fd;
	char	*line;
	char	*map;

	map = NULL;
	game->map_game.height_map = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_error("File couldn't be opened. Is the file correct?\n", 2, game);
	while (1)
	{
		line = get_next_line(fd)
		if (!line_tmp)
			break ;
		if (line_tmp == '\n')
		{
			free(line_tmp);
			continue ;
		}
		map = ft_join_gnl(map, line_tmp);
		free(line);
		if (!map)
			ft
	}

}*/

void	ft_parsing(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		ft_error("Invalid number of inputs\n", 1, game);
	ft_map_type(argv, game);
}
