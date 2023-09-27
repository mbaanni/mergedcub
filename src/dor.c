/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:38:41 by mbaanni           #+#    #+#             */
/*   Updated: 2023/09/27 14:41:56 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

float	bound_angle(float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	else if (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	dor_click(mlx_key_data_t key, void *ptr)
{
	t_mlx *mlx;
	int mx;
	int my;

	mlx = (t_mlx *)ptr;
	if (key.key == MLX_KEY_E && mlx_is_key_down(mlx->mlx, key.key))
	{
		mx = (mlx->movex + cos(mlx->angle) * BLOCSIZE) / BLOCSIZE;
		my = (mlx->movey + sin(mlx->angle) * BLOCSIZE) / BLOCSIZE;
		if (mlx->map[my][mx] == 'C')
		{
			mlx->start = 1;
			mlx->map[my][mx] = 'O';
		}
		else if (mlx->map[my][mx] == 'O')
		{
			mlx->start = 1;
			mlx->map[my][mx] = 'C';
		}
	}
}