/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:00:26 by mbaanni           #+#    #+#             */
/*   Updated: 2023/10/04 08:48:00 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	mouse_scroll(t_mlx *mlx)
{
	static int	x;
	int			y;
	int			post;

	post = x;
	mlx_get_mouse_pos(mlx->mlx, &x, &y);
	if (x == post)
		return ;
	mlx->start = 1;
	if (post > x)
		mlx->angle -= ANGLE_SPEED * 2;
	if (post < x)
		mlx->angle += ANGLE_SPEED * 2;
	if (mlx->angle >= 2 * M_PI)
		mlx->angle -= 2 * M_PI;
	if (mlx->angle < 0)
		mlx->angle += 2 * M_PI;
	if (x > WIDTH || x < 0)
	{
		x = HEIGHT / 2;
		mlx_set_mouse_pos(mlx->mlx, x, HEIGHT / 2);
	}
}

void	check_next_xy(t_mlx *mlx, int x, int y)
{
	int	offsetx;
	int	offsety;

	offsetx = 8;
	offsety = 8;
	if (x < 0)
		offsetx = -offsetx;
	if (y < 0)
		offsety = -offsety;
	if ((mlx->map[(int)((mlx->movey + y + offsety) / BLOCSIZE)][(int)(mlx->movex
		/ BLOCSIZE)]) != '1' && (mlx->map[(int)((mlx->movey + y
		+ offsety) / BLOCSIZE)][(int)(mlx->movex
		/ BLOCSIZE)]) != 'C')
	{
		mlx->movey += y;
		mlx->start = 1;
	}
	if (mlx->map[(int)(mlx->movey / BLOCSIZE)][(int)((mlx->movex + x + offsetx)
			/ BLOCSIZE)] != '1' && mlx->map[(int)(mlx->movey
			/ BLOCSIZE)][(int)((mlx->movex + x + offsetx) / BLOCSIZE)] != 'C')
	{
		mlx->movex += x;
		mlx->start = 1;
	}
}

void	player_movement(t_mlx *mlx)
{
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_W))
		check_next_xy(mlx, cos(mlx->angle) * PLAYER_SPEED, sin(mlx->angle)
			* PLAYER_SPEED);
	else if (mlx_is_key_down(mlx->mlx, MLX_KEY_S))
		check_next_xy(mlx, -cos(mlx->angle) * PLAYER_SPEED, -sin(mlx->angle)
			* PLAYER_SPEED);
	else if (mlx_is_key_down(mlx->mlx, MLX_KEY_D))
		check_next_xy(mlx, cos(mlx->angle + M_PI / 2) * PLAYER_SPEED,
			sin(mlx->angle + M_PI / 2) * PLAYER_SPEED);
	else if (mlx_is_key_down(mlx->mlx, MLX_KEY_A))
		check_next_xy(mlx, cos(mlx->angle - M_PI / 2) * PLAYER_SPEED,
			sin(mlx->angle - M_PI / 2) * PLAYER_SPEED);
}

void	player_angle(t_mlx *mlx)
{
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_RIGHT))
	{
		mlx->angle += ANGLE_SPEED;
		if (mlx->angle >= 2 * M_PI)
			mlx->angle -= 2 * M_PI;
		mlx->start = 1;
	}
	else if (mlx_is_key_down(mlx->mlx, MLX_KEY_LEFT))
	{
		mlx->angle -= ANGLE_SPEED;
		if (mlx->angle < 0)
			mlx->angle += 2 * M_PI;
		mlx->start = 1;
	}
}

void	event_win(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx->mlx);
		delete_texter(mlx);
		mlx_terminate(mlx->mlx);
		custom_exit(1);
	}
	player_movement(mlx);
	player_angle(mlx);
	if (BONUS)
		mouse_scroll(mlx);
}
