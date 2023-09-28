/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:58:52 by mtaib             #+#    #+#             */
/*   Updated: 2023/09/28 13:42:01 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"
#include <stdio.h>

int		is_valid_charset(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != ' '
			&& !ft_strchr("NSEWCO", str[i])) //added 'CO'
			return (1);
	}
	return (0);
}

int		check_chars(char **map)
{
	int		i;
	int		j;
	char	c;

	c = '\0';
	i = -1;
	while (map[++i])
	{
		j = -1;
		if (is_valid_charset(map[i]))
			return (print_error(16));
		while (map[i][++j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				if (get_player()->x)
					return (print_error(13));
				get_player()->x = j * BLOCSIZE;
				get_player()->y = i * BLOCSIZE;
				printf("here x = %d y = %d\n", get_player()->x, get_player()->y);
				c = map[i][j];
				map[i][j] = '0';
			}
		}
	}
	if (!c)
		return (print_error(7));
	return (c);
}
