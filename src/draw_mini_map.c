/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:09:20 by mbaanni           #+#    #+#             */
/*   Updated: 2023/09/23 07:42:44 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void    put_pixel(int color, t_mlx *mlx, int x, int y)
{
    int i;
    int j;

    i = 0;
    while (i < BLOCSIZE)
    {
        j = 0;
        while (j < BLOCSIZE)
        {
			if (j != 0 && i != 0)
            	mlx_put_pixel(mlx->minimap_img, (x + j)*map_size, (y + i)*map_size, color);
            j++;
        }
        i++;
    }
}

int drow_map(t_mlx *mlx)
{
    int i;
    int j;
    i = 0;
    j = 0;
    while (mlx->map[i][j] && mlx->map[i][j] != '\n')
    {
        if (mlx->map[i][j] == '1')
            put_pixel(0xffffffff, mlx, j*BLOCSIZE, i*BLOCSIZE);
        if (mlx->map[i][j] == '0')
            put_pixel(0x000000ff, mlx, j*BLOCSIZE, i*BLOCSIZE);
        j++;
		if ((!mlx->map[i][j] || mlx->map[i][j] == '\n') && mlx->map[i+1])
		{
			i++;
			j = 0;
		}
    }
    return (0);
}