/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elemnts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:15:14 by mtaib             #+#    #+#             */
/*   Updated: 2023/09/23 07:33:48 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"
#include <stdio.h>

int		checkPath(char *path)
{	
	void	*ptr;
	
	ptr = mlx_load_png(path);
	if (!ptr)
		return (printError(4));
	free(ptr);
	return (0);
}

int		isDirection(char *str)
{
	if (!ft_strncmp("NO", str, -1))
		return (0);
	else if (!ft_strncmp("SO", str, -1))
		return (0);
	else if (!ft_strncmp("WE", str, -1))
		return (0);
	else if (!ft_strncmp("EA", str, -1))
		return (0);
	else if (!ft_strncmp("C", str, -1))
		return (0);
	else if (!ft_strncmp("F", str, -1))
		return (0);
	return (1);
}

int		countPoint(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ',')
			count++;
	}
	return (count);
}

int		checkDirs(char *str)
{
	int		i;
	int		n[3];
	int		j;

	j = 0;
	i = -1;
	if (countPoint(str) != 2)
		return (printError(2));
	
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9') 
			&& str[i] != ',' && str[i] != ' ' && str[i] != '\t'
			&& str[0] != '-' && str[0] != '+')
			return (printError(2));
	i = 0;
	while(str[i])
	{
		if (str[i] == ',')
			return (printError(2));
		n[j] = ft_atoi(&str[i]);
		getType()->colors[j] = n[j];
		if (n[j] < 0 || n[j] > 255)
			return (printError(2));
		while (str[i] && str[i] != ',')
			i++;
		if (str[i] == ',' && !str[i + 1])
			return (printError(2));
		if (str[i])
			i++;
		if (j <= 2)
			j++;
	}
	if (str && str[i - 2] == ',')
		return (printError(2));
	return (0);
}

int		checkDuplicates(t_dirs *dirs, char *str)
{
	while (dirs)
	{
		if (!ft_strncmp(dirs->key, str, ft_strlen(str)))
			return (1);
		dirs = dirs->next;
	}
	return (0);
}

int		printError(int	i)
{
	printf("Error :\n");
	if (i == 0)
		printf("\tInvalid direction\n");
	else if (i == 1)
		printf("\tDoes not has a color value\n");
	else if (i == 2)
		printf("\tInvalid color value\n");
	else if (i == 3)
		printf("\tDuplication error\n");
	else if (i == 4)
		printf("\tInvalid path\n");
	else if (i == 5)
		printf("\tmap must be surounded by walls\n");
	else if (i == 6)
		printf("\tInvalid borders\n");
	else if (i == 7)
		printf("\tInvalid player value\n");
	else if (i == 8)
		printf("\tInvalid player borders\n");
	else if (i == 9)
		printf("\tMap not found\n");
	else if (i == 10)	
		printf("\tInvalid file name\n)");
	else if (i == 11)	
		printf("\tBad file descriptor\n");
	else if (i == 12)
			printf("\tInvald map position\n");
	else if (i == 13)
			printf("\tDuplicated player value\n");
	else if (i == 14)
			printf("\tNew line musnt be in map\n");
	else if (i == 15)
			printf("\tInvalid size\n");
	else if (i == 16)
			printf("\tInvald map\n");
	return (1);
}

int		isDirs(t_dirs *dirs, char *str)
{
	int		i;

	i = 0;
	while (dirs)
	{
		if (ft_strncmp("NO", str, ft_strlen(str)))
			return (1);
		else if (ft_strncmp("SO", str, ft_strlen(str)))
			return (1);
		else if (ft_strncmp("WE", str, ft_strlen(str)))
			return (1);
		else if (ft_strncmp("EA", str, ft_strlen(str)))
			return (1);
		i++;
		dirs = dirs->next;
	}
	if (i == 4)
		return (0);
	return (1);
}

int		checkElements(char	*str)
{
	int		i;
	char	**params;
	char	*arg;

	i = -1;
	if (str[0] == '\n')
		return (0);
	arg = ft_strtrim(str, " \n\t");
	while (arg[++i])
		if (arg[i] == ' ') //|| arg[i] == '\t')
			break ;
	if (!arg[i])
		return (printError(0));
	params = malloc(sizeof(char *) * 3);
	if (!params)
		return (1);
	params[0] = ft_substr(arg, 0, i);
	while (arg[i] && arg[i] == ' ')
	   i++;
	if (!arg[i] && params[0][0] != 'C' && params[0][0] != 'F')	
	{		
		return (printError(0));
	}
	else if (!arg[i] && (params[0][0] == 'C' || params[0][0] == 'F'))
		return (printError(1));
	params[1] = ft_substr(arg, i , ft_strlen(arg));
	params[2] = NULL;
	if (isDirection(params[0]))
		return (printError(0));

	if (params[0][0] == 'C' || params[0][0] == 'F')
	{
		if (checkDirs(params[1]))
			return (1);
	}
	// else if (params[0][0] != 'C' && params[0][0] != 'F')	
	// 	return (checkPath(params[1]));
	if (checkDuplicates(getType()->directions, params[0]))
		return (printError(3));
	getType()->dirNbs++;
	lstadd_back(&getType()->directions
		, lstnew(params[0], params[1]));
	free(str);
	// + or - in last 
	// swap color value 
	return (0);	
}
