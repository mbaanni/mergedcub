/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:09:20 by mbaanni           #+#    #+#             */
/*   Updated: 2023/09/27 14:51:09 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	ft_clean(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (RADIUS + 1) * 2)
	{
		j = -1;
		while (++j < (RADIUS + 1) * 2)
			mlx_put_pixel(mlx->minimap_img, j, i, 0);
	}
}

int	calculate_dist(int px, int py, int dstx1, int dsty1)
{
	int	dist;

	dist = sqrt(pow((dstx1 - px), 2) + pow((dsty1 - py), 2));
	return (dist);
}

void	put_on_minimap(t_mlx *mlx, int x, int y, int color)
{
	int	dx;
	int	dy;
	int	nx;
	int	ny;

	dx = mlx->movex - RADIUS;
	dy = mlx->movey - RADIUS;
	if (calculate_dist(mlx->movex, mlx->movey, x, y) <= RADIUS)
	{
		nx = x - dx;
		ny = y - dy;
		if (nx >= 0 && ny >= 0 && nx < WIDTH && ny < HEIGHT)
			mlx_put_pixel(mlx->minimap_img, nx, ny, color);
	}
}

void	put_pixel(int color, t_mlx *mlx, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	x *= BLOCSIZE;
	y *= BLOCSIZE;
	while (i < BLOCSIZE)
	{
		j = 0;
		while (j < BLOCSIZE)
		{
			if (j != 0 && i != 0)
				put_on_minimap(mlx, (x + j), (y + i), color);
			j++;
		}
		i++;
	}
}

int	drow_map(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (mlx->map[i][j] && mlx->map[i][j] != '\n')
	{
		if (mlx->map[i][j] == '1')
			put_pixel(0xffffffff, mlx, j, i);
		else if (mlx->map[i][j] == '0')
			put_pixel(0x000000ff, mlx, j, i);
		else if (mlx->map[i][j] == 'O')
			put_pixel(0x0000ffff, mlx, j, i);
		else if (mlx->map[i][j] == 'C')
			put_pixel(0x000fffff, mlx, j, i);
		j++;
		if ((!mlx->map[i][j] || mlx->map[i][j] == '\n') && mlx->map[i + 1])
		{
			i++;
			j = 0;
		}
	}
	return (0);
}