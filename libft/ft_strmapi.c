/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:36:23 by mmedjahe          #+#    #+#             */
/*   Updated: 2023/11/20 17:59:25 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s2;
	unsigned int	i;
	char			c;

	if (!s)
		return (NULL);
	i = ft_strlen((char *)s);
	s2 = malloc((ft_strlen((char *)s) + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	s2[i] = '\0';
	if (!s2)
		return (NULL);
	i = 0;
	while (s[i])
	{
		c = *(char *)(s + i);
		s2[i] = f(i, c);
		i++;
	}
	return (s2);
}
