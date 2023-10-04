/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:12:49 by mtaib             #+#    #+#             */
/*   Updated: 2023/10/04 08:21:09 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D_bonus.h"

t_dirs	*lstnew(char *key, char *path)
{
	t_dirs	*newnode;

	newnode = my_alloc(sizeof(t_dirs));
	if (!newnode)
		return (0);
	newnode->key = key;
	newnode->path = path;
	newnode->next = 0;
	return (newnode);
}

void	lstadd_back(t_dirs **lst, t_dirs *newnode)
{
	t_dirs	*tmp;

	tmp = *lst;
	if (*lst)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newnode;
	}
	else
		*lst = newnode;
}
