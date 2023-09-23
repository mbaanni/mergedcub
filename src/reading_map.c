/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 08:01:51 by mbaanni           #+#    #+#             */
/*   Updated: 2023/09/23 07:42:11 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Cub3D.h"

int parse_map(t_mlx *mlx)
{
    int i;
    int j;
    i = 0;
    while (mlx->map[i])
    {
        j = 0;
        while (mlx->map[i][j])
        {
            if (mlx->map[i][j] == 'P')
            {
                mlx->map[i][j] = '0';
                mlx->movex = (j * BLOCSIZE)+BLOCSIZE/2;
                mlx->movey = (i * BLOCSIZE)+BLOCSIZE/2;
                mlx->angle = PI/2;
            }
            j++;
        }
        i++;
    }

    mlx->map_hight = (i-1)*BLOCSIZE;
    mlx->map_width = (j-1)*BLOCSIZE;
    return (0);
}

char **read_it(int fd)
{
    char	*line;
	char	*str;
	char	**map;

	str = 0;
    map = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		str = ft_strjoin(str, line);
		str = ft_strjoin(str, " ");
		free(line);
	}
	map = ft_split(str, ' ');
	free(str);
	close(fd);
	if (!map)
		write(1, "not allocated\n", 14);
	return (map);
}

char **open_map(char *link)
{
    int fd;
    fd = open(link, O_RDONLY);
    if (fd < 0)
        return (0);
    return (read_it(fd));
}
