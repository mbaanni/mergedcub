/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:25:22 by mbaanni           #+#    #+#             */
/*   Updated: 2023/09/29 22:12:41 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	set_point(t_mlx *mlx, float	*pos[2], float	*pblock[2], char flag)
{
	if (flag == 'v')
	{
		pos[X] = &mlx->ray->vx;
		pos[Y] = &mlx->ray->vy;
		pblock[X] = &mlx->ray->vxblock;
		pblock[Y] = &mlx->ray->vyblock;
		mlx->max = mlx->map_width;
	}
	else
	{
		pos[X] = &mlx->ray->hx;
		pos[Y] = &mlx->ray->hy;
		pblock[X] = &mlx->ray->hxblock;
		pblock[Y] = &mlx->ray->hyblock;
		mlx->max = mlx->map_hight;
	}
}

void	last_wall_hit(t_mlx *mlx, char flag)
{
	int		inc;
	int		mp[2];
	float	*pos[2];
	float	*pblock[2];

	inc = -1;
	set_point(mlx, pos, pblock, flag);
	while (++inc < mlx->max)
	{
		mp[X] = *pos[X] / BLOCSIZE;
		mp[Y] = *pos[Y] / BLOCSIZE;
		if (mp[Y] < 0 || mp[X] < 0 || mp[X] > mlx->map_width
			|| mp[Y] > mlx->map_hight)
			break ;
		if (!mlx->map[mp[Y]] || !mlx->map[mp[Y]][mp[X]])
			break ;
		if (mlx->map[mp[Y]][mp[X]] && (mlx->map[mp[Y]][mp[X]] == '1'
				|| mlx->map[mp[Y]][mp[X]] == 'C'))
			break ;
		*pos[X] += *pblock[X];
		*pos[Y] += *pblock[Y];
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
	last_wall_hit(mlx, 'h');
}

void	calculate_vertical(float ra, t_mlx *mlx, t_ray *ray)
{
	float	tang;

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
	last_wall_hit(mlx, 'v');
}
