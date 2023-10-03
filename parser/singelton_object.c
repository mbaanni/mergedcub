/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singelton_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:35:14 by mtaib             #+#    #+#             */
/*   Updated: 2023/10/03 19:20:37 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

t_mapinfo	*get_type(void)
{
	static t_mapinfo	*mapinfo;

	if (!mapinfo)
	{
		mapinfo = my_alloc(sizeof(t_mapinfo));
		if (!mapinfo)
			return (0);
		mapinfo->directions = NULL;
		mapinfo->map = NULL;
		mapinfo->dirnbs = 0;
		mapinfo->p_value = 0;
	}
	return (mapinfo);
}

t_player	*get_player(void)
{
	static t_player	*player;

	if (!player)
	{
		player = my_alloc(sizeof(t_player));
		if (!player)
			return (0);
		player->x = 0;
		player->y = 0;
	}
	return (player);
}
