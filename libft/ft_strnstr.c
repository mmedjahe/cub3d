/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:38:21 by mmedjahe          #+#    #+#             */
/*   Updated: 2023/11/20 18:01:02 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_s2;
	size_t	i;

	i = 0;
	if (!len && !big)
		return (0);
	if (little[i] == '\0')
		return ((char *)big);
	len_s2 = ft_strlen((char *)little);
	if (!len_s2)
		return ((char *)big);
	while (big[i] && i + len_s2 <= len)
	{
		if (!ft_memcmp(big + i, little, len_s2))
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
