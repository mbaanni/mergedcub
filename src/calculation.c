/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:25:22 by mbaanni           #+#    #+#             */
/*   Updated: 2023/09/27 10:15:37 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"
#include <stdio.h>

float	small_dist(t_ray *ray, t_mlx *mlx)
{
	double	v_dist_sqr;
	double	h_dist_sqr;
	float	dist;
	int mx;
	int my;
	v_dist_sqr = pow((ray->vx - mlx->movex),2) + pow((ray->vy - mlx->movey),2);
	h_dist_sqr = pow((ray->hx - mlx->movex),2) + pow((ray->hy - mlx->movey),2);
	if (h_dist_sqr > v_dist_sqr)
	{
		ray->rx = ray->vx;
		ray->ry = ray->vy;
		dist = sqrt(v_dist_sqr);
		mlx->offset = fmod(ray->vy, BLOCSIZE);
		mlx->side = RIGHT;
		if (ray->vxblock > 0)
			mlx->side = LEFT;
	}
	else
	{
		ray->rx = ray->hx;
		ray->ry = ray->hy;
		dist = sqrt(h_dist_sqr);
		mlx->offset = fmod(ray->hx, BLOCSIZE);
		mlx->side = TOP;
		if (ray->hyblock < 0)
			mlx->side = BOTTOM;
	}
	mx = ray->ry / BLOCSIZE;
	my = ray->rx / BLOCSIZE;
	if (mx > 0 && my > 0 && mx < mlx->map_width &&  my < mlx->map_hight && mlx->map[my][mx] == 'C')
		mlx->side = DOR;
	return dist;
}

void	calculate_horizontal(float ra, t_mlx *mlx, t_ray *ray)
{
	float	tang;
	int		mx;
	int		my;
	int		x;

	tang = -tan(ra);
	if (ra > M_PI)
	{
		ray->hy = (int)(mlx->movey / BLOCSIZE) * BLOCSIZE - 0.001;
		ray->hx = mlx->movex + (mlx->movey - ray->hy) / tang;
		ray->hyblock = -BLOCSIZE;
		ray->hxblock = -ray->hyblock / tang;
	}
	if (ra < M_PI)
	{
		ray->hy = ((int)(mlx->movey / BLOCSIZE) * BLOCSIZE) + BLOCSIZE;
		ray->hx = mlx->movex + (mlx->movey - ray->hy) / tang;
		ray->hyblock = BLOCSIZE;
		ray->hxblock = -ray->hyblock / tang;
	}
	x = 0;
	while (x < mlx->map_hight)
	{
		mx = ray->hx / BLOCSIZE;
		my = ray->hy / BLOCSIZE;
		if (my < 0 || mx < 0 || mx > mlx->map_width || my > mlx->map_hight)
			break ;
		if (!mlx->map[my] || !mlx->map[my][mx])
			break ;
		if (mlx->map[my][mx] && (mlx->map[my][mx] == '1'
				|| mlx->map[my][mx] == 'C'))
			break ;
		ray->hx = ray->hx + ray->hxblock;
		ray->hy = ray->hy + ray->hyblock;
		x++;
	}
}

void	calculate_vertical(float ra, t_mlx *mlx, t_ray *ray)
{
	float	tang;
	int		mx;
	int		my;
	int		x;

	tang = -tan(ra);
	if (ra > (3 * M_PI) / 2 || ra < M_PI / 2)
	{
		ray->vx = (int)(mlx->movex / BLOCSIZE) * BLOCSIZE + BLOCSIZE;
		ray->vy = mlx->movey + (mlx->movex - ray->vx) * tang;
		ray->vxblock = BLOCSIZE;
		ray->vyblock = -ray->vxblock * tang;
	}
	if (ra > (M_PI / 2) && ra < (3 * M_PI / 2))
	{
		ray->vx = (int)(mlx->movex / BLOCSIZE) * BLOCSIZE - 0.001;
		ray->vy = mlx->movey + (mlx->movex - ray->vx) * tang;
		ray->vxblock = -BLOCSIZE;
		ray->vyblock = -ray->vxblock * tang;
	}
	x = 0;
	while (x < mlx->map_width)
	{
		mx = ray->vx /BLOCSIZE;
		my = ray->vy / BLOCSIZE;
		if (my < 0 || mx < 0 || mx > mlx->map_width || my > mlx->map_hight)
			break ;
		if (!mlx->map[my] || !mlx->map[my][mx])
			break ;
		if (mlx->map[my][mx] && (mlx->map[my][mx] == '1'
				|| mlx->map[my][mx] == 'C'))
			break ;
		ray->vx = ray->vx + ray->vxblock;
		ray->vy = ray->vy + ray->vyblock;
		x++;
	}
}
