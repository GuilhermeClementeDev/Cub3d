/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:46:05 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/11 17:28:28 by guclemen         ###   ########.fr       */
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

static int	ft_words(const char *s, int c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 1;
	if (!s || !*s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	if (s[i] == '\0')
		count++;
	if (s[0] != c)
		count++;
	return (count);
}

static void	ft_allocword(char **ptrs, const char *s, int c)
{
	unsigned int	i;
	unsigned int	k;
	unsigned int	start;

	i = 0;
	k = 0;
	while (1)
	{
		start = i;
		while (s[i] && s[i] != c)
			i++;
		ptrs[k] = (char *)ft_calloc((i - start) + 1, 1);
		ft_strlcpy(ptrs[k], &s[start], (i - start) + 1);
		k++;
		if (!s[i])
			break ;
		i++;
	}
	ptrs[k] = NULL;
}

char	**ft_split_cub3d(char const *s, char c)
{
	char			**ptrs;
	unsigned int	words;

	if (!s)
		return (NULL);
	words = ft_words(s, c);
	ptrs = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!ptrs)
		return (NULL);
	ft_allocword(ptrs, s, c);
	return (ptrs);
}
