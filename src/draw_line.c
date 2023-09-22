/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:10:28 by mbaanni           #+#    #+#             */
/*   Updated: 2023/09/16 09:44:46 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void    draw_line(mlx_image_t *image, int startx, int starty, int endx, int endy, int color)
{
	int	delta_x;
	int	delta_y;
    int step_x;
    int step_y;
    int error;
    int error2;

    step_x = 1;
    step_y = 1;
    error2 = 0;
    delta_x = endx - startx;
    delta_y = endy - starty;
    if (delta_x < 0)
	{
		delta_x = -delta_x;
        step_x = -1;
	}
    if (delta_y < 0)
	{
		delta_y = -delta_y;
        step_y = -1;
	}
	delta_y*=-1;
    error = delta_y+delta_x;
    while (1)
    {
        if (startx >= 0 && startx < WIDTH && starty >= 0 && starty < HEIGHT)
    		mlx_put_pixel(image, startx, starty, color);
		if (startx == endx && starty == endy)
			break;
		error2 = error*2;
		if (error2 >= delta_y)
		{
			if (startx == endx)
				break;
			error+=delta_y;
			startx+=step_x;
		}
		if (error2 <= delta_x)
		{
			if (starty == endy)
				break;
			error+=delta_x;
			starty+=step_y;
		}
	}
}