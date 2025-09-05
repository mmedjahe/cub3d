/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:56:23 by mmedjahe          #+#    #+#             */
/*   Updated: 2023/12/11 17:56:25 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *form, ...)
{
	int		len;
	int		i;
	va_list	args;

	if (!form)
		return (0);
	len = 0;
	i = 0;
	va_start(args, form);
	while (form[i])
	{
		if (form[i] == '%')
		{
			i++;
			len += ft_print_formatted(args, form[i]);
		}
		else
			len += write(1, &form[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}
