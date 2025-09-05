/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:39:37 by mmedjahe          #+#    #+#             */
/*   Updated: 2023/11/17 18:26:30 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	length(int nbr)
{
	int	n;
	int	len;

	len = 0;
	n = nbr;
	if (n < 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_positive(int n)
{
	char	*s;
	int		i;
	long	nbr;

	s = NULL;
	nbr = n;
	s = malloc((length(nbr) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = length(nbr);
	s[i] = '\0';
	while (i--)
	{
		s[i] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (s);
}

char	*ft_negative(int n)
{
	long	nbr;
	char	*s;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nbr = -n;
	s = malloc((length(nbr) + 2) * sizeof(char));
	if (!s)
		return (NULL);
	i = length(nbr) + 1;
	s[0] = '-';
	s[i] = '\0';
	while (--i)
	{
		s[i] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (s);
}

char	*ft_zero(void)
{
	char	*res;

	res = malloc(2 * sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '0';
	res[1] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	if (n > 0)
		return (ft_positive(n));
	else if (n < 0)
		return (ft_negative(n));
	else
		return (ft_zero());
}
