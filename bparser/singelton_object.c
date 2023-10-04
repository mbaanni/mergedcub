/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singelton_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:35:14 by mtaib             #+#    #+#             */
/*   Updated: 2023/10/04 08:21:24 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D_bonus.h"

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
