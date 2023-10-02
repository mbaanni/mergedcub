/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:57:04 by mbaanni           #+#    #+#             */
/*   Updated: 2023/09/29 22:17:03 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

float	dist_point(int startx, int starty, float endx, float endy)
{
	return (sqrt(pow((endx - startx), 2) + pow((endy - starty), 2)));
}

float	wall_calculation(float *distray, float angle_step, int r, float *wall)
{
	float	wall_strip_hight;

	if (*distray < 0)
		*distray = 1;
	*distray = cos(30 * M_PI / 180 - (r * angle_step)) * (*distray);
	wall_strip_hight = (BLOCSIZE / *distray) * 1200;
	wall[START] = (HEIGHT / 2) - (wall_strip_hight / 2);
	wall[END] = (HEIGHT / 2) + (wall_strip_hight / 2);
	if (wall[START] < 0)
		wall[START] = 0;
	return (wall_strip_hight);
}

uint32_t	get_color(t_mlx *mlx, int y, int x)
{
	int			pos;
	uint32_t	value[4];

	pos = (y * mlx->tile[mlx->side]->width + x)
		* mlx->tile[mlx->side]->bytes_per_pixel;
	if (pos < 0 || pos > (int)(mlx->tile[mlx->side]->height
		* (mlx->tile[mlx->side]->width * 4)) - 4)
		return (0);
	value[0] = mlx->tile[mlx->side]->pixels[pos] << 24;
	value[1] = mlx->tile[mlx->side]->pixels[pos + 1] << 16;
	value[2] = mlx->tile[mlx->side]->pixels[pos + 2] << 8;
	value[3] = mlx->tile[mlx->side]->pixels[pos + 3];
	return (value[0] | value[1] | value[2] | value[3]);
}

void	check_dore(t_mlx *mlx)
{
	int	mx;
	int	my;

	mx = mlx->rx / BLOCSIZE;
	my = mlx->ry / BLOCSIZE;
	if (mlx->side == RIGHT)
		mx -= 1;
	else if (mlx->side == BOTTOM)
		my -= 1;
	if (mx >= 0 && my >= 0 && mx < mlx->map_width && my < mlx->map_hight
		&& mlx->map[my][mx] == 'C')
		mlx->side = DOR;
}

float	small_dist(t_ray *ray, t_mlx *mlx)
{
	float	v_dist;
	float	h_dist;
	float	dist;

	v_dist = dist_point(mlx->movex, mlx->movey, ray->vx, ray->vy);
	h_dist = dist_point(mlx->movex, mlx->movey, ray->hx, ray->hy);
	mlx->rx = ray->hx;
	mlx->ry = ray->hy;
	dist = h_dist;
	mlx->offset = fmod(ray->hx, BLOCSIZE);
	mlx->side = TOP;
	if (ray->hyblock < 0)
		mlx->side = BOTTOM;
	if (h_dist > v_dist)
	{
		mlx->rx = ray->vx;
		mlx->ry = ray->vy;
		dist = v_dist;
		mlx->offset = fmod(ray->vy, BLOCSIZE);
		mlx->side = RIGHT;
		if (ray->vxblock > 0)
			mlx->side = LEFT;
	}
	check_dore(mlx);
	return (dist);
}
