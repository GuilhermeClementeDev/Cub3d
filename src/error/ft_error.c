/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:01:46 by guclemen          #+#    #+#             */
/*   Updated: 2025/09/04 19:07:36 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_simple_error(char *msg, int ret)
{
	if (msg)
	{
		ft_putstr_fd("Error :(\n", 2);
		ft_putstr_fd(msg, 2);
	}
	exit (ret);
}
