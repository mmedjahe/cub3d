/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:58:47 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/09/05 21:48:44 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft.h"

char	*get_next_line(int fd)
{
	static char	stack[BUFFER_SIZE + 1];
	char		*statik;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	statik = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!statik)
		return (NULL);
	statik[0] = '\0';
	ft_memcpy(statik, stack, ft_strlen(stack));
	statik[ft_strlen(stack)] = '\0';
	line = checkboucle(fd, &statik);
	ft_memcpy(stack, statik, ft_strlen(statik));
	stack[ft_strlen(statik)] = '\0';
	return (free(statik), line);
}

int	rline(int fd, char **statik)
{
	char	*buffer;
	int		res;
	char	*newstatik;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	res = read(fd, buffer, BUFFER_SIZE);
	buffer[res] = '\0';
	if (res == -1)
		return (-1);
	(newstatik = ft_strjoin(*statik, buffer));
	free(*statik);
	(*statik = newstatik);
	free(buffer);
	return (res);
}

char	*checkboucle(int fd, char **statik)
{
	int	res;

	while (1)
	{
		if (ft_strchr(*statik, '\n'))
			return (removeline(statik));
		res = rline(fd, statik);
		if (res == 0)
		{
			if (*statik[0])
				return (removeline(statik));
			return (NULL);
		}
		if (res == -1)
			return (NULL);
	}
}

char	*removeline(char **statik)
{
	int		x;
	int		i;
	char	*finalstring;
	char	*nstatik;

	nstatik = *statik;
	x = 0;
	i = (ft_strlen(*statik));
	while (nstatik[x] && nstatik[x] != '\n')
		x++;
	if (nstatik[x] == '\n')
		x++;
	finalstring = malloc(sizeof(char) * (x + 1));
	if (!finalstring)
		return (NULL);
	ft_memcpy(finalstring, nstatik, x);
	finalstring[x] = '\0';
	ft_memcpy(nstatik, nstatik + x, i - x);
	nstatik[i - x] = '\0';
	*statik = nstatik;
	return (finalstring);
}
