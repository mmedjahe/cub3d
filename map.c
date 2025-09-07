/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:31:11 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/09/07 22:03:45 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map(t_cub *cub)
{
	player_count(cub);
	is_map_closed(cub);
	if (cub->height < 3 || cub->width < 3)
		ft_error("map too short", cub);
	get_player_loc(cub);
}

void	is_map_closed(t_cub *cub)
{
	char	**map;
	char	c;
	int		y;
	int		x;

	y = 0;
	map = rectang_map(cub, cub->map);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			c = map[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				check_cell_closed(map, y, x, cub);
			x++;
		}
		if (cub->width < x)
			cub->width = x;
		y++;
	}
	free_tab(map);
	cub->height = y;
}

void	player_count(t_cub *cub)
{
	int	count;
	int	i;
	int	x;

	count = 0;
	i = -1;
	while (cub->map[++i])
	{
		x = 0;
		while (cub->map[i][x])
		{
			if (cub->map[i][x] == 'N' || cub->map[i][x] == 'S'
				|| cub->map[i][x] == 'W' || cub->map[i][x] == 'E')
				count++;
			x++;
		}
	}
	if (count != 1)
		ft_error("map should contains only one starting position", cub);
}

void	get_player_loc(t_cub *cub)
{
	int	i;
	int	x;

	i = -1;
	while (cub->map[++i])
	{
		x = 0;
		while (cub->map[i][x])
		{
			if (cub->map[i][x] == 'N' || cub->map[i][x] == 'S'
				|| cub->map[i][x] == 'E' || cub->map[i][x] == 'W')
			{
				cub->player->player_y = (double)i + 0.5;
				cub->player->player_x = (double)x + 0.5;
				cub->player->player_direction = get_direction(cub->map[i][x]);
				return ;
			}
			x++;
		}
	}
}

char	**rectang_map(t_cub *cub, char **original_map)
{
	size_t	y;
	size_t	width;
	char	**new_map;
	size_t	i;

	i = 0;
	y = 0;
	width = 0;
	while (original_map[y])
	{
		if (ft_strlen(original_map[y]) > width)
			width = ft_strlen(original_map[y]);
		y++;
	}
	new_map = malloc(sizeof(char *) * (y + 1));
	if (!new_map)
		ft_error("malloc failed", cub);
	while (i < y)
	{
		new_map[i] = copy_and_pad_line(original_map[i], width, cub);
		i++;
	}	
	new_map[y] = NULL;
	return (new_map);
}
