/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:43:00 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/09 19:01:03 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_is_config(char *line)
{
	int	size;

	size = ft_strlen(line);
	if (!line)
		return (0);
	if (size >= 1)
	{
		if (line[0] == 'C' && line[1] == ' ')
			return (1);
		if (line[0] == 'F' && line[1] == ' ')
			return (1);
	}
	if (size >= 2)
	{
		if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
			return (1);
		if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
			return (1);
		if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
			return (1);
		if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
			return (1);
	}
	return (0);
}

static void	ft_config_line(char *config, t_game *game)
{
	if (config[0] == 'N')
		game->map_game.no_texture = ft_strdup(&config[3]);
	else if (config[0] == 'E')
		game->map_game.ea_texture = ft_strdup(&config[3]);
	else if (config[0] == 'S')
		game->map_game.so_texture = ft_strdup(&config[3]);
	else if (config[0] == 'W')
		game->map_game.we_texture = ft_strdup(&config[3]);
	else if (config[0] == 'C')
		game->map_game.ceiling_color = ft_strdup(&config[2]);
	else if (config[0] == 'F')
		game->map_game.floor_color = ft_strdup(&config[2]);
}

static void	ft_create_map(char **map_file, t_game *game)
{
	int	i;

	i = 0;
	ft_map_height(map_file, game);
	game->map_game.map = malloc(sizeof(char *) * (game->map_game.height + 1));
	if (!game->map_game.map)
		ft_error("", 3, game);
	while (i < game->map_game.height)
	{
		game->map_game.map[i] = ft_strdup(map_file[i]);
		if (!game->map_game.map[i])
			ft_error("", 3, game);
		i++;
	}
	game->map_game.map[i] = NULL;
	game->map_game.malloc = 1;
	ft_map_width(game);
}

static void	ft_structuring_reading(char *file, t_game *game)
{
	char	**lines;
	int		i;
	int		config;

	i = 0;
	lines = ft_split(file, '\n');
	free(file);
	while (lines[i])
	{
		if (lines[i][0] != '\0')
		{
			config = ft_is_config(lines[i]);
			if (config)
				ft_config_line(lines[i], game);
			else if (!config && lines[i][0] != '\n')
			{
				ft_create_map(&lines[i], game);
				break ;
			}
		}
		i++;
	}
	ft_free_matrix(lines);
}

void	ft_read_file(char *argv, t_game *game)
{
	int		fd;
	char	*line;
	char	*file;

	file = NULL;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_error("File couldn't be opened. Is the file correct?\n", 2, game);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		file = ft_join_gnl(file, line);
		free(line);
		if (!file)
			ft_error("", 3, game);
	}
	close(fd);
	ft_structuring_reading(file, game);
}
