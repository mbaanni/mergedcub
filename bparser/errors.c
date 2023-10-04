/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 10:11:35 by mtaib             #+#    #+#             */
/*   Updated: 2023/10/04 08:20:58 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D_bonus.h"

void	print_map_error(int i)
{
	if (i == 5)
		printf("\tmap must be surounded by walls\n");
	else if (i == 6)
		printf("\tInvalid borders\n");
	else if (i == 7)
		printf("\tInvalid player value\n");
	else if (i == 9)
		printf("\tMap not found\n");
	else if (i == 12)
		printf("\tInvalid map position\n");
	else if (i == 13)
		printf("\tDuplicated player value\n");
	else if (i == 14)
		printf("\tNew line musnt be in map\n");
	else if (i == 16)
		printf("\tInvalid map\n");
}

int	print_error(int i)
{
	printf("Error :\n");
	if (i == 0)
		printf("\tInvalid direction\n");
	else if (i == 1)
		printf("\tDoes not has a color value\n");
	else if (i == 2)
		printf("\tInvalid color value\n");
	else if (i == 3)
		printf("\tDuplication error\n");
	else if (i == 4)
		printf("\tInvalid path\n");
	else if (i == 10)
		printf("\tInvalid file name\n)");
	else if (i == 11)
		printf("\tBad file descriptor\n");
	print_map_error(i);
	return (1);
}
