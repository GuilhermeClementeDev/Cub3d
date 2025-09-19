/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:18:30 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/18 12:27:21 by guclemen         ###   ########.fr       */
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

static int	is_space(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
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
		if (is_space(ptrs[k]))
		{
			free(ptrs[k]);
			ptrs[k] = (char *)ft_calloc(1, 1);
		}
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
