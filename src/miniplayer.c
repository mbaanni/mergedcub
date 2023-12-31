/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniplayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:50:25 by mbaanni           #+#    #+#             */
/*   Updated: 2023/10/04 08:44:44 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	delete_texter(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (mlx->tile[i] && i < 4)
	{
		mlx_delete_texture(mlx->tile[i]);
		i++;
	}
}

void	draw_miniplayer(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < 8)
	{
		x = 0;
		while (x < 8)
		{
			put_on_minimap(mlx, (mlx->movex) + x, (mlx->movey) + y, 0xff0000ff);
			x++;
		}
		y++;
	}
}
