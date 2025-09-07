/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:36:14 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/09/07 21:45:25 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_colors(int *dest, char **tab, t_cub *cub)
{
	int	i;
	int	value;

	i = 0;
	while (tab[i])
	{
		value = ft_atoi(tab[i]);
		if (value < 0 || value > 255)
		{
			free_tab(tab);
			ft_error("color out of range", cub);
		}
		dest[i] = value;
		i++;
	}
}

char	**parse_color_line(char *str, t_cub *cub)
{
	int		i;
	char	**tab;

	i = 0;
	while (ft_isdigit(str[i]) != 1)
		i++;
	if (comma_counter(str + i) != 2)
		ft_error("color line format error", cub);
	tab = ft_split(str + i, ',');
	if (!tab[0] || !tab[1] || !tab[2] || tab[3])
		ft_error("wrong number of color components", cub);
	return (tab);
}