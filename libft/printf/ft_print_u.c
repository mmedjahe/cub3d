/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:56:09 by mmedjahe          #+#    #+#             */
/*   Updated: 2023/12/11 17:56:11 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_u_len(unsigned int nbr)
{
	size_t	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static void	rec_print_u(unsigned int nbr)
{
	if (nbr > 9)
	{
		rec_print_u(nbr / 10);
		rec_print_u(nbr % 10);
	}
	else
		ft_putchar_fd(nbr + 48, 1);
}

int	ft_print_u(unsigned int nbr)
{
	rec_print_u(nbr);
	return (get_u_len(nbr));
}
