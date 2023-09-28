/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singelton_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:35:14 by mtaib             #+#    #+#             */
/*   Updated: 2023/09/28 13:40:51 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

t_mapInfo*		get_type(void)
{
	static t_mapInfo 	*mapInfo;

	if (!mapInfo)
	{
		mapInfo = malloc(sizeof(t_mapInfo));
		if (!mapInfo)
			return (0);
		mapInfo->directions = NULL;
		mapInfo->map = NULL;
		mapInfo->dirNbs = 0;
	}
	return (mapInfo);
}

t_player*	get_player(void)
{
	static t_player *player;

	if (!player)
	{
		player = malloc(sizeof(t_player));
		if (!player)
			return (0);
		player->x = 0;
		player->y = 0;
	}
	return (player);
}
