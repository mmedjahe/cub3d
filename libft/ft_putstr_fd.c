/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:28:47 by mmedjahe          #+#    #+#             */
/*   Updated: 2023/11/20 17:58:46 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int				i;
	unsigned char	*s2;

	if (!s)
		return ;
	s2 = (unsigned char *)s;
	i = 0;
	while (s2[i])
	{
		write(fd, &s2[i], 1);
		i++;
	}
}
