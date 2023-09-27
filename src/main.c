/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 10:20:15 by mbaanni           #+#    #+#             */
/*   Updated: 2023/09/27 14:58:13 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	load_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", 0);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->minimap_img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx->mlx, mlx->img, 0, 0);
	mlx_image_to_window(mlx->mlx, mlx->minimap_img, 0, 0);
}

int	load_image(t_mlx *mlx)
{
	mlx->tile[0] = mlx_load_png("img/steel.png");
	if (mlx->tile[0]->width != mlx->tile[0]->height)
		write(1, "Img not square\n", 15);
	mlx->tile[1] = mlx_load_png("img/steel.png");
	if (mlx->tile[1]->width != mlx->tile[1]->height)
		write(1, "Img not square\n", 15);
	mlx->tile[2] = mlx_load_png("img/holeskin.png");
	if (mlx->tile[2]->width != mlx->tile[2]->height)
		write(1, "Img not square\n", 15);
	mlx->tile[3] = mlx_load_png("img/holeskin.png");
	if (mlx->tile[3]->width != mlx->tile[3]->height)
		write(1, "Img not square\n", 15);
	mlx->tile[4] = mlx_load_png("img/door.png");
	if (mlx->tile[4]->width != mlx->tile[4]->height)
		write(1, "Img not square\n", 15);
	return (0);
}

void	set_value(t_mlx *mlx)
{
	getType()->mlx = mlx;
	mlx->map = getType()->map;
	mlx->movex = get_player()->x;
	mlx->movey = get_player()->y;
	mlx->movex += BLOCSIZE / 2;
	mlx->movey += BLOCSIZE / 2;
	mlx->map_hight = getType()->max_y;
	mlx->map_width = getType()->max_x;
	mlx->max = mlx->map_hight;
	if (mlx->map_width > mlx->map_hight)
		mlx->max = mlx->map_width;
	mlx->angle = M_PI;
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac != 2)
		return (1);
	ft_memset(&mlx, 0, sizeof(mlx));
	if (mapParsing(*(av + 1)))
		return (1);
	set_value(&mlx);
	if (load_image(&mlx))
	{
		write(2, "Failed to load image\n", 21);
		exit(1);
	}
	load_mlx(&mlx);
	mlx.start = 1;
	mlx_key_hook(mlx.mlx, dor_click, &mlx);
	mlx_loop_hook(mlx.mlx, event_win, &mlx);
	mlx_loop_hook(mlx.mlx, drow_player, &mlx);
	mlx_loop(mlx.mlx);
	mlx_terminate(mlx.mlx);
}
