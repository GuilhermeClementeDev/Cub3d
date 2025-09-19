/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfaustin <yfaustin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:14:43 by yfaustin          #+#    #+#             */
/*   Updated: 2025/09/19 18:48:45 by yfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	validate_rgb_values(char **split_value)
{
	int	i;
	int	value;
	int	j;

	i = 0;
	while (i < 3)
	{
		if (!split_value[i] || split_value[i][0] == '\0')
			return (0);
		j = 0;
		while (split_value[i][j])
		{
			if (!ft_isdigit(split_value[i][j]))
				return (0);
			j++;
		}
		value = ft_atoi(split_value[i]);
		if (value < 0 || value > 255)
			return (0);
		i++;
	}
	return (1);
}

static int	validate_color_format(char *str)
{
	int	comma_count;
	int	i;

	comma_count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == ',')
			comma_count++;
		else if (!ft_isdigit(str[i]) && str[i] != ' ')
			return (0);
		i++;
	}
	return (comma_count == 2);
}

static char	*trim_leading_spaces(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (str);
}

unsigned int	create_trgb(char *str)
{
	unsigned int	color;
	char			**split_value;
	t_color			trgb;

	if (!validate_color_format(str))
		return (0);
	split_value = ft_split(trim_leading_spaces(str), ',');
	if (!split_value || !split_value[0] || !split_value[1] || !split_value[2])
	{
		if (split_value)
			free_split(split_value);
		return (0);
	}
	if (!validate_rgb_values(split_value))
	{
		free_split(split_value);
		return (0);
	}
	trgb.t = 255;
	trgb.r = ft_atoi(split_value[0]);
	trgb.g = ft_atoi(split_value[1]);
	trgb.b = ft_atoi(split_value[2]);
	free_split(split_value);
	color = (unsigned int)trgb.t << 24 | trgb.r << 16 | trgb.g << 8 | trgb.b;
	return (color);
}
