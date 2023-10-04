/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:15:14 by mtaib             #+#    #+#             */
/*   Updated: 2023/10/04 08:21:14 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D_bonus.h"

int	is_all_value(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int	check_door_borders(int i, int j)
{
	char	**map;

	map = get_type()->map;
	if (!((map[i - 1][j] == '1' && map[i + 1][j] == '1') || (map[i][j
				- 1] == '1' && map[i][j + 1] == '1')))
		return (print_error(6));
	return (0);
}

int	valid_borders(int i, int j)
{
	char	**map;

	map = get_type()->map;
	if ((i > 0 && map[i - 1][j] == ' ') || (map[i + 1] && (map[i
				+ 1][j] == ' ')) || (j > 0 && map[i][j - 1] == ' ') || (j > 0
			&& map[i][j + 1] == ' '))
		return (print_error(6));
	return (0);
}

int	empty_line(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\n' && str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
