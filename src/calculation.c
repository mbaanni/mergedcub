/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:25:22 by mbaanni           #+#    #+#             */
/*   Updated: 2023/09/25 17:59:08 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"
#include <stdio.h>

int line_end_n(char *str)
{
    int i;

    i = 0;
    while (str[i] && (str[i] != ' ' || str[i] != '\t'))
        i++;
    return (i);
}

int len_2d(char **str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;   
}

void	small_dist(t_ray *ray, t_mlx *mlx, float *distray)
{
    double  v_dist_sqr;
    double  h_dist_sqr;
    v_dist_sqr = ((ray->vx - mlx->movex) * (ray->vx - mlx->movex)) + ((ray->vy - mlx->movey) * (ray->vy - mlx->movey));
	h_dist_sqr = ((ray->hx - mlx->movex) * (ray->hx - mlx->movex)) + ((ray->hy - mlx->movey) * (ray->hy - mlx->movey));
    if (h_dist_sqr > v_dist_sqr)
    {
        ray->rx = ray->vx;
        ray->ry = ray->vy;
        *distray = sqrt(v_dist_sqr);
        mlx->offset = fmod(ray->vy, BLOCSIZE);
        mlx->side = RIGHT;
        if (ray->vxblock > 0)
            mlx->side = LEFT;
    }
    else {
        ray->rx = ray->hx;
        ray->ry = ray->hy;
        *distray = sqrt(h_dist_sqr);
        mlx->offset = fmod(ray->hx, BLOCSIZE);
        mlx->side = TOP;
        if (ray->hyblock < 0)
            mlx->side = BOTTOM;
    }
    if (mlx->map[(int)ray->ry/BLOCSIZE][(int)ray->rx/BLOCSIZE] == 'C')
        mlx->side = DOR;
}

void    calculate_horizontal(float ra, t_mlx *mlx, t_ray *ray)
{
    float   tang;
    int     mx;
    int     my;
    int     x;

    tang = -tan(ra);
    if (ra > M_PI)
    {
		ray->hy = (int)(mlx->movey / BLOCSIZE ) * BLOCSIZE;
		ray->hx = mlx->movex + (mlx->movey - ray->hy)/tang;
		ray->hyblock = -BLOCSIZE;
		ray->hxblock = -ray->hyblock/tang;
    }
	if(ra < M_PI)
	{
		ray->hy = ((int)(mlx->movey / BLOCSIZE) * BLOCSIZE) + BLOCSIZE;
		ray->hx = mlx->movex + (mlx->movey - ray->hy)/tang;
		ray->hyblock = BLOCSIZE;
		ray->hxblock = -ray->hyblock/tang;
	}
    x = 0;
	while(x < mlx->max)
	{
		mx = ray->hx/BLOCSIZE;
		my = ray->hy/BLOCSIZE - 1 * (ra > M_PI);
		if (my <= 0 || my >= len_2d(mlx->map) || mx <= 0 || mx >= line_end_n(mlx->map[my]))
			break ;
        if (!mlx->map[my] || !mlx->map[my][mx])
            break;
		if (mlx->map[my][mx] && (mlx->map[my][mx] == '1' || mlx->map[my][mx] == 'C'))
			break;
		ray->hx = ray->hx + ray->hxblock;
		ray->hy = ray->hy + ray->hyblock;
        x++;
	}
}

void    calculate_vertical(float ra, t_mlx *mlx, t_ray *ray)
{
    float   tang;
    int     mx;
    int     my;
    int x;

    tang = -tan(ra);
    if (ra > (3*M_PI)/2 ||  ra < M_PI/2)
    {
        ray->vx = ((int)(mlx->movex / BLOCSIZE ) * BLOCSIZE ) + BLOCSIZE;
        ray->vy = mlx->movey + (mlx->movex - ray->vx) * tang;
        ray->vxblock = BLOCSIZE;
        ray->vyblock = -ray->vxblock*tang;
    }
	
    if (ra > (M_PI/2) && ra < (3*M_PI/2))
    {
        ray->vx = ((int)(mlx->movex / BLOCSIZE ) * BLOCSIZE );
        ray->vy = mlx->movey + (mlx->movex - ray->vx) * tang;
        ray->vxblock = -BLOCSIZE;
        ray->vyblock = -ray->vxblock*tang;
    }
    x = 0;
    while (x < mlx->max)
    {
        mx = ray->vx/BLOCSIZE - 1 * (ra > (M_PI/2) && ra < (3*M_PI/2));
        my = ray->vy/BLOCSIZE;
        if (my <= 0 || my >= len_2d(mlx->map) || mx <= 0 || mx >= line_end_n(mlx->map[my]))
			break ;
        if (!mlx->map[my] || !mlx->map[my][mx])
            break;
		if (mlx->map[my][mx] && (mlx->map[my][mx] == '1' || mlx->map[my][mx] == 'C'))
			break;
		ray->vx = ray->vx + ray->vxblock;
		ray->vy = ray->vy + ray->vyblock;
        x++;
    }
}
