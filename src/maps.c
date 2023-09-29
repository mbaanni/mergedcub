/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:11:12 by mbaanni           #+#    #+#             */
/*   Updated: 2023/09/29 22:15:37 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

float	dist(float px, float py, float rx, float ry)
{
	float	dx;
	float	dy;
	float	res;

	dx = rx - px;
	dy = ry - py;
	res = sqrt((dx * dx) + (dy * dy));
	return (res);
}

void	draw_block(mlx_image_t *img, int start, int end, int ray)
{
	uint32_t	color;

	if (start == 0)
		color = 0x45b3e0ff;
	else
		color = 0xffffff00;
	while (start < end)
	{
		mlx_put_pixel(img, ray, start, color);
		start++;
	}
}

void	draw_wall(t_mlx *mlx, t_ray *ray, int r, float distray)
{
	float		wall_strip_hight;
	uint32_t	color;
	float		wall[2];
	int			texter[2];

	wall[START] = 0;
	wall_strip_hight = wall_calculation(&distray, ray->angle_step, r, wall);
	texter[X] = mlx->offset * ((int)(mlx->tile[mlx->side]->width / BLOCSIZE));
	if (mlx->side == TOP || mlx->side == RIGHT)
		texter[X] = mlx->tile[mlx->side]->width - texter[X];
	draw_block(mlx->img, 0, HEIGHT / 2, r);
	while (wall[START] < wall[END] && wall[START] < HEIGHT)
	{
		texter[Y] = (1.0 - (wall[END] - wall[START]) / wall_strip_hight)
			* (mlx->tile[mlx->side]->height);
		color = get_color(mlx, texter[Y], texter[X]);
		mlx_put_pixel(mlx->img, r, wall[START], color);
		wall[START]++;
	}
	draw_block(mlx->img, wall[END], HEIGHT, r);
}

void	draw_ray(t_mlx *mlx)
{
	t_ray	ray;
	int		r;
	float	ra;
	float	distray;

	r = -1;
	mlx->ray = &ray;
	ray.angle_step = (FIELD_OF_VIEW * (M_PI / 180)) / WIDTH;
	ra = mlx->angle - ((float)FIELD_OF_VIEW / 2) * (M_PI / 180);
	while (++r < WIDTH)
	{
		ra = bound_angle(ra);
		calculate_horizontal(ra, mlx, &ray);
		calculate_vertical(ra, mlx, &ray);
		distray = small_dist(&ray, mlx);
		draw_wall(mlx, &ray, r, distray);
		ra += ray.angle_step;
	}
}

void	drow_player(void *ptr)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)ptr;
	if (mlx->start)
	{
		ft_clean(mlx);
		drow_map(mlx);
		draw_ray(mlx);
		draw_miniplayer(mlx);
		mlx->start = 0;
	}
}
