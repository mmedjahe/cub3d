/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:54:20 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/09/07 22:03:37 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_cell_closed(char **map, int y, int x, t_cub *cub)
{
	if (y == 0 || !map[y + 1] || x == 0 || !map[y][x + 1])
	{
		free_tab(map);
		ft_error("map not closed (border)", cub);
	}
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' ||
		map[y][x - 1] == ' ' || map[y][x + 1] == ' ' ||
		x >= (int)ft_strlen(map[y - 1]) || x >= (int)ft_strlen(map[y + 1]))
	{
		free_tab(map);
		ft_error("map not closed", cub);
	}
}

char	*copy_and_pad_line(char *src, size_t width, t_cub *cub)
{
	size_t	len;
	char	*line;

	len = ft_strlen(src);
	line = malloc(sizeof(char) * (width + 1));
	if (!line)
		ft_error("malloc failed", cub);
	ft_memcpy(line, src, len);
	while (len < width)
		line[len++] = ' ';
	line[len] = '\0';
	return (line);
}

double	get_direction(char c)
{
	if (c == 'N')
		return (M_PI / 2);
	else if (c == 'S')
		return (3 * M_PI / 2);
	else if (c == 'E')
		return (0);
	else if (c == 'W')
		return (M_PI);
	return (0);
}
