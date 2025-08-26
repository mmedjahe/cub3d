/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:51:58 by mmedjahe          #+#    #+#             */
/*   Updated: 2025/07/17 23:04:02 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_set(char const *set, int c)
{
	int	i;

	if (!set)
		return (0);
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	istart;
	size_t	iend;

	if (s1 == NULL || set == NULL)
		return (NULL);
	istart = 0;
	iend = ft_strlen((char *)s1);
	while (s1[istart] && ft_check_set(set, s1[istart]))
		istart++;
	while (iend > istart && ft_check_set(set, s1[iend - 1]))
		iend--;
	s2 = malloc((iend - istart + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, ((char *)(s1 + istart)), (iend - istart + 1));
	return (s2);
}
