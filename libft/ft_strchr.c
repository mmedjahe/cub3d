/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:10:53 by mmedjahe          #+#    #+#             */
/*   Updated: 2023/11/20 18:00:53 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	d;

	i = 0;
	d = c;
	if (d == 0)
		return ((char *)(s + ft_strlen((char *)s)));
	while (s[i])
	{
		if (s[i] == d)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}
