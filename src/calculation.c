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
		mlx->rx = ray->vx;
		mlx->ry = ray->vy;
		dist = sqrt(v_dist_sqr);
		mlx->offset = fmod(ray->vy, BLOCSIZE);
		mlx->side = RIGHT;
		if (ray->vxblock > 0)
			mlx->side = LEFT;
	}
	else
	{
		mlx->rx = ray->hx;
		mlx->ry = ray->hy;
		dist = sqrt(h_dist_sqr);
		mlx->offset = fmod(ray->hx, BLOCSIZE);
		mlx->side = TOP;
		if (ray->hyblock < 0)
			mlx->side = BOTTOM;
	}
	mx = mlx->ry / BLOCSIZE;
	my = mlx->rx / BLOCSIZE;
	if (mx > 0 && my > 0 && mx < mlx->map_width &&  my < mlx->map_hight && mlx->map[my][mx] == 'C')
		mlx->side = DOR;
	return dist;
}

void	last_wall_hit(t_mlx *mlx, t_ray *ray, char flag)
{
	int		x;
	int		mp[2];
	float	*pos[2];
	float	*pblock[2];
	int		max;

	x = 0;
	pos[X] = &ray->vx;
	pos[Y] = &ray->vy;
	pblock[X] = &ray->vxblock;
	pblock[Y] = &ray->vyblock;
	max = mlx->map_width;
	if (flag == 'h')
	{
		pos[X] = &ray->hx;
		pos[Y] = &ray->hy;
		pblock[X] = &ray->hxblock;
		pblock[Y] = &ray->hyblock;
		max = mlx->map_hight;
	}
	while (x < max)
	{
		mp[X] = *pos[x] / BLOCSIZE;
		mp[Y] = *pos[Y] / BLOCSIZE;
		if (mp[Y] < 0 || mp[X] < 0 || mp[X] > mlx->map_width || *pos[Y] > mlx->map_hight)
			break ;
		if (!mlx->map[mp[Y]] || !mlx->map[mp[Y]][mp[X]])
			break ;
		if (mlx->map[mp[Y]][mp[X]] && (mlx->map[mp[Y]][mp[X]] == '1'
				|| mlx->map[mp[Y]][mp[X]] == 'C'))
			break ;
		*pos[x] = *pos[x] + *pblock[X];
		*pos[Y] = *pos[Y] + *pblock[Y];
		x++;
	}
}

void	calculate_horizontal(float ra, t_mlx *mlx, t_ray *ray)
{
	float	tang;

	tang = -tan(ra);
	if (ra > M_PI)
	{
		ray->hy = (int)(mlx->movey / BLOCSIZE) * BLOCSIZE - 0.001;
		ray->hyblock = -BLOCSIZE;
	}
	if (ra < M_PI)
	{
		ray->hy = ((int)(mlx->movey / BLOCSIZE) * BLOCSIZE) + BLOCSIZE;
		ray->hyblock = BLOCSIZE;
	}
	ray->hx = mlx->movex + (mlx->movey - ray->hy) / tang;
	ray->hxblock = -ray->hyblock / tang;
	last_wall_hit(mlx, ray, 'h');

}

void	calculate_vertical(float ra, t_mlx *mlx, t_ray *ray)
{
	float	tang;
	int		mx;
	int		my;

	tang = -tan(ra);
	if (ra > (3 * M_PI) / 2 || ra < M_PI / 2)
	{
		ray->vx = (int)(mlx->movex / BLOCSIZE) * BLOCSIZE + BLOCSIZE;
		ray->vxblock = BLOCSIZE;
	}
	if (ra > (M_PI / 2) && ra < (3 * M_PI / 2))
	{
		ray->vx = (int)(mlx->movex / BLOCSIZE) * BLOCSIZE - 0.001;
		ray->vxblock = -BLOCSIZE;
	}
	ray->vy = mlx->movey + (mlx->movex - ray->vx) * tang;
	ray->vyblock = -ray->vxblock * tang;
	last_wall_hit(mlx, ray, 'v');
}
