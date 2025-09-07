/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:59:34 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/09/07 21:50:20 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parser(t_cub *cub, char *file)
{
	int		fd;
	char	*line;
	t_node	*list;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("cannot open your file", cub);
	verif_file_format(file, cub);
	line = textures_and_colors(fd, cub);
	if (!check_textures_and_colors(cub))
	{
		free(line);
		ft_error("color or texture missing", cub);
	}
	fill_map_list(&list, cub, fd, line);
	final_fill(&list, cub);
	free_list(&list);
	verif_map(cub);
	close(fd);
	return (0);
}

int	sorter(char *str, t_cub *cub)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!ft_strncmp(str + i, "F ", 2))
		return (1);
	else if (!ft_strncmp(str + i, "C ", 2))
		return (2);
	else if (!ft_strncmp(str + i, "NO ", 3))
		text_paths_stocker(&cub->NO, str + i, cub);
	else if (!ft_strncmp(str + i, "SO ", 3))
		text_paths_stocker(&cub->SO, str + i, cub);
	else if (!ft_strncmp(str + i, "WE ", 3))
		text_paths_stocker(&cub->WE, str + i, cub);
	else if (!ft_strncmp(str + i, "EA ", 3))
		text_paths_stocker(&cub->EA, str + i, cub);
	else if (is_line_empty(str))
		return (3);
	else
		return (4);
	return (0);
}

int	is_line_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	ground_colors_stockers(char *str, t_cub *cub)
{
	char	**tab;

	if (cub->ground_colors[0] != -1)
		ft_error("ground colors appears two times", cub);
	tab = parse_color_line(str, cub);
	fill_colors(cub->ground_colors, tab, cub);
	free_tab(tab);
}

void	ceiling_colors_stockers(char *str, t_cub *cub)
{
	char	**tab;

	if (cub->ceiling_colors[0] != -1)
		ft_error("ceiling colors appears two times", cub);
	tab = parse_color_line(str, cub);
	fill_colors(cub->ceiling_colors, tab, cub);
	free_tab(tab);
}
