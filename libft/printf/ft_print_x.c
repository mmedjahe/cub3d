/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:56:17 by mmedjahe          #+#    #+#             */
/*   Updated: 2023/12/11 17:56:19 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned int n, char format)
{
	int		count;
	char	hex_digit;

	count = 0;
	if (n >= 16)
	{
		count += ft_print_hex(n / 16, format);
	}
	if (format == 'x')
		hex_digit = "0123456789abcdef"[n % 16];
	else
		hex_digit = "0123456789ABCDEF"[n % 16];
	count += write(1, &hex_digit, 1);
	return (count);
}

int	ft_print_x(char format, unsigned int n)
{
	int	count;

	count = 0;
	count += ft_print_hex(n, format);
	return (count);
}
