/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:15:14 by mtaib             #+#    #+#             */
/*   Updated: 2023/09/24 20:47:13 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"
#include <stdio.h>

int	check_path(char *path)
{
	mlx_texture_t	*ptr;

	ptr = mlx_load_png(path);
	if (!ptr)
		return (print_error(4));
	free(ptr);
	return (0);
}

int	count_point(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ',')
			count++;
	}
	return (count);
}

int	save_colors_value(int i, int j, char dir, char *str)
{
	int	*n;

	n = my_alloc(3 * sizeof(int));
	if (!n)
		return (1);
	while (str[i] && ++j < 3)
	{
		if (str[i] == ',')
			return (print_error(2));
		n[j] = ft_atoi(&str[i]);
		if (n[j] < 0 || n[j] > 255)
			return (print_error(2));
		while (str[i] && str[i] != ',')
			i++;
		if (str[i] == ',' && !str[i + 1])
			return (print_error(2));
		if (str[i])
			i++;
	}
	if (dir == 'C')
		get_type()->c_color = n;
	else
		get_type()->f_color = n;
	return (0);
}

int	check_dirs(char dir, char *str)
{
	int	i;

	i = -1;
	if (count_point(str) != 2)
		return (print_error(2));
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != ',' && str[0] != '-'
			&& str[i] != '+')
			return (print_error(2));
	return (save_colors_value(0, -1, dir, str));
}
