/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:00:26 by mbaanni           #+#    #+#             */
/*   Updated: 2023/09/27 12:13:03 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void    mouse_scroll(t_mlx *mlx)
{
    static int x;
    int y;
    int curent;
    int post;
    post = x;
    mlx_get_mouse_pos(mlx->mlx, &x, &y);
    if (x == post)
        return ;
    mlx->start = 1;
    if (post > x)
        mlx->angle -= angle_speed*2;
    if (post < x)
        mlx->angle += angle_speed*2;
    if (mlx->angle >= 2*PI)
        mlx->angle -= 2*PI;
    if (mlx->angle < 0)
        mlx->angle += 2*PI;
    if (x > WIDTH || x < 0)
    {
        x = HEIGHT/2;
        mlx_set_mouse_pos(mlx->mlx, x, HEIGHT/2);
    }
}

void    dor_click(mlx_key_data_t key, void *ptr)
{
    t_mlx * mlx;
    int mx;
    int my;
    
    mlx = (t_mlx *) ptr;
    if (key.key == MLX_KEY_E && mlx_is_key_down(mlx->mlx, key.key))
    {
        mx = (mlx->movex + cos(mlx->angle)*BLOCSIZE) / BLOCSIZE;
        my = ( mlx->movey + sin(mlx->angle)*BLOCSIZE) / BLOCSIZE;
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

void	check_next_xy(t_mlx *mlx, int x, int y)
{
    int offsetx = 8;
    int offsety = 8;
    if (x < 0)
        offsetx = -offsetx;
    if (y < 0)
        offsety = -offsety;
    if ((mlx->map[(int)((mlx->movey + y + offsety)/BLOCSIZE)][(int)(mlx->movex/BLOCSIZE)]) != '1' && (mlx->map[(int)((mlx->movey + y + offsety)/BLOCSIZE)][(int)(mlx->movex/BLOCSIZE)]) != 'C')
	{
        mlx->movey += y;
        mlx->start = 1;
	}
    if (mlx->map[(int)(mlx->movey/BLOCSIZE)][(int)((mlx->movex + x + offsetx) /BLOCSIZE)] != '1' && mlx->map[(int)(mlx->movey/BLOCSIZE)][(int)((mlx->movex + x + offsetx) /BLOCSIZE)] != 'C')
    {
        mlx->movex += x;
        mlx->start = 1;
    }
}

void    player_movement(t_mlx *mlx)
{
    int x;

    x = 1;
    if (mlx_is_key_down(mlx->mlx, MLX_KEY_R))
        x = 2;
    if (mlx_is_key_down(mlx->mlx, MLX_KEY_W))
        check_next_xy(mlx, cos(mlx->angle) * PLAYER_SPEED * x,
			sin(mlx->angle) * PLAYER_SPEED * x);
    else if (mlx_is_key_down(mlx->mlx, MLX_KEY_S))
		check_next_xy(mlx, -cos(mlx->angle) * PLAYER_SPEED * x,
			-sin(mlx->angle)*PLAYER_SPEED * x);
    else if (mlx_is_key_down(mlx->mlx, MLX_KEY_D))
		check_next_xy(mlx, cos(mlx->angle+PI/2)*PLAYER_SPEED * x,
			sin(mlx->angle+PI/2)*PLAYER_SPEED * x);
    else if (mlx_is_key_down(mlx->mlx, MLX_KEY_A))
		check_next_xy(mlx, cos(mlx->angle-PI/2)*PLAYER_SPEED * x,
			sin(mlx->angle-PI/2)*PLAYER_SPEED * x);
}

void	player_angle(t_mlx *mlx)
{
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_RIGHT))
    {
        mlx->angle += angle_speed;
        if (mlx->angle >= 2*PI)
            mlx->angle -= 2*PI;
	    mlx->start = 1;
    }
    else if (mlx_is_key_down(mlx->mlx, MLX_KEY_LEFT))
    {
        mlx->angle -= angle_speed;
        if (mlx->angle < 0)
            mlx->angle += 2*PI;
	    mlx->start = 1;
    }
}

void event_win(void *param)
{
    t_mlx *mlx;

    mlx = (t_mlx *)param;    
    if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
    {
		mlx_close_window(mlx->mlx);
		exit(0);
    }
    player_movement(mlx);
    player_angle(mlx);
    //mouse_scroll(mlx);
}
