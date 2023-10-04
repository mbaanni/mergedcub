/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:58:52 by mtaib             #+#    #+#             */
/*   Updated: 2023/10/04 08:20:53 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D_bonus.h"

int	check_file_name(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (i < 4)
		return (1);
	if (!(str[i] == 'b' && str[i - 1] == 'u' 
			&& str[i - 2] == 'c' && str[i - 3] == '.'))
		return (1);
	return (0);
}

int	max_len(void)
{
	int		max;
	int		i;
	char	**map;

	map = get_type()->map;
	max = ft_strlen(map[0]);
	i = 0;
	while (map[++i])
		if (max < ft_strlen(map[i]))
			max = ft_strlen(map[i]);
	return (max);
}

int	check_borders(char **map, char c)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == c)
			{
				if (i == 0 || !map[i + 1])
					return (print_error(5));
				if ((i > 0 && j == 0) || (j > 0 && !map[i][j + 1]))
					return (print_error(5));
				if (valid_borders(i, j))
					return (1);
				if (c == 'C')
					if (check_door_borders(i, j))
						return (1);
			}
		}
	}
	return (0);
}

int	check_map_errors(char **map)
{
	char	c;

	c = check_chars(map, -1, -1);
	if ((int)c == 1)
		return (1);
	if (check_borders(map, c))
		return (1);
	if (check_borders(map, '0'))
		return (1);
	if (BONUS)
	{
		if (check_borders(map, 'C') || check_borders(map, 'O'))
			return (1);
	}
	return (0);
}
