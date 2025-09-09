/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:36:14 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/09/08 21:13:36 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_colors(int *dest, char **tab)
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
			return (0);
		}
		dest[i] = value;
		i++;
	}
	return (1);
}

char	**parse_color_line(char *str, t_cub *cub)
{
	int		i;
	char	**tab;

	i = 1;
	while (str[i] == ' ')
		i++;
	if (!ft_isdigit(str[i]))
	{
		free(str);
		ft_error("color line error", cub);
	}
	if (comma_counter(str + i) != 2)
	{
		free(str);
		ft_error("color line format error", cub);
	}
	tab = ft_split(str + i, ',');
	if (!tab[0] || !tab[1] || !tab[2] || tab[3])
	{
		free_tab(tab);
		free(str);
		ft_error("wrong number of color components", cub);
	}
	validate_color_components(tab, cub, str);
	return (tab);
}

int	is_valid_number(char *s)
{
	int	i;
	int	digit_found;

	if (!s)
		return (0);
	i = 0;
	while (s[i] == ' ')
		i++;
	digit_found = 0;
	while (ft_isdigit(s[i]))
	{
		digit_found = 1;
		i++;
	}
	while (s[i] == ' ')
		i++;
	if (!digit_found)
		return (0);
	return (s[i] == '\0');
}

void	validate_color_components(char **tab, t_cub *cub, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < 3)
	{
		tmp = ft_strtrim(tab[i], " \n\t\r");
		free(tab[i]);
		tab[i] = tmp;
		if (!is_valid_number(tab[i]))
		{
			free(str);
			free_tab(tab);
			ft_error("invalid color component", cub);
		}
		i++;
	}
}
