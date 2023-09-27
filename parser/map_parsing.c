/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:58:52 by mtaib             #+#    #+#             */
/*   Updated: 2023/09/27 10:15:31 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"
#include <stdio.h>

int		checkFileName(char *str)
{
	int		i;

	i = ft_strlen(str) - 1;
	if (i < 4)
		return (1);
	if (!(str[i] == 'b' && str[i - 1] == 'u'
		&& str[i - 2] == 'c' && str[i - 3] == '.'))
		return (1);
	return (0);
}

int		check_max_values()
{
	int		max_x;
	int		i;
	int		j;
	char	**map;

	map = getType()->map;
	j = 0;
	max_x = ft_strlen(map[0]);
	i = -1;
	while (map[++i])
	{
		if (max_x < ft_strlen(map[i]))
			max_x = ft_strlen(map[i]); 
	}
	getType()->max_y = i;
	getType()->max_x = max_x;
	//if (i * BLOCSIZE > HEIGHT || j * BLOCSIZE > WIDTH)
	//		return(printError(15));
	return (0);
}

int		checkValidWay(char **map, char c)
{
	int		i;
	int		j;
	
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == c)
			{
				if (i == 0 || !map[i + 1])
					return (printError(5));
				if (map[i + 1][j] == '\n')
					break ; 
				if ((i > 0 && (map[i - 1][j] == ' ' || !map[i - 1][j]))
						|| (map[i + 1] && (map[i + 1][j] == ' ' || !map[i + 1][j]))
						|| (j > 0 && (map[i][j - 1] == ' ' || !map[i][j - 1]))
						|| (j > 0 && (map[i][j + 1] == ' ' || !map[i][j + 1]))
						|| (!map[i][j + 1])
						)
					return (printError(6));
			}
		}
	}
	return (0);
}
int		is_value(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != ' '
			&& !ft_strchr("NSEWCOX", str[i])) //added 'COX'
			{
				return (1);
			}
	}
	return (0);
}

int		checkChars(char **map)
{
	int		i;
	int		j;
	int		dup;
	char	c;

	dup = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		if (is_value(map[i]))
			return (printError(16));
		while (map[i][++j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				get_player()->x = j * BLOCSIZE;
				get_player()->y = i * BLOCSIZE;
				c = map[i][j];
				dup++;
				map[i][j] = '0';
			}
		}
		if (dup > 1)
			return (printError(13));
	}
	
	if (!dup)
		return (printError(7));
	return (c);
}


int		checkMapErrors(char **map)
{
	char	c;

	c = checkChars(map);
	if ((int)c == 1)
		return (1);
	if (checkValidWay(map, '0'))
		return (1);
	if (check_max_values())
		return (1);
	return (0);

}
int		is_all_value(char *str, char c)
{
	int		i;
	
	i = 0;
	while (str[i] && str[i + 1]) //&& str[i + 1])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}
int		handleMap(int	fd)
{
	char	*line;
	char	*str;

	str = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n')
			str = ft_strjoin(str, line);
		if (str && line[0] == '\n')
		{
			while (1)
			{
				line = get_next_line(fd);
				if (!line)
					break ;
				if (line[0] != '\n')
					str = ft_strjoin(str, line);
				if (line[0] != '\n' && !is_all_value(line, ' '))
					return (printError(16));
			}
			break ;
		}
	}
	if (!str || (str[0] == '\n' && !str[1]))
		return (printError(9));
	getType()->map = ft_split(str, '\n');
	if (checkMapErrors(getType()->map))
		return (1);
	int		i;
	char	**map;

	map = getType()->map;
	i = -1;
	return (0);
}

int		handleDirs(int 	fd)
{
	char	*line;
	
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (getType()->dirNbs < 6
				&& (line[0] == '0' || line[0] == '1')
				&& !ft_strchr(line, ','))
			return (printError(12));
		if (checkElements(line))
			return (1);
		if (getType()->dirNbs == 6)
		{
			if (handleMap(fd))
				return (1);
			return (0);
		}
	}
	return (0);
}

int		mapParsing(char *str)
{
	int		fd;
	
	if (checkFileName(str))
		return (printError(10));
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (printError(11));
	if (handleDirs(fd))
		return (1);
	return (0);
}
