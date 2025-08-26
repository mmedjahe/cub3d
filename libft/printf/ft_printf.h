/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:56:29 by mmedjahe          #+#    #+#             */
/*   Updated: 2023/12/11 17:56:31 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *form, ...);
int	ft_print_formatted(va_list args, char form);
int	ft_print_c(const char c);
int	ft_print_s(const char *str);
int	ft_print_p(void *ptr);
int	ft_print_di(const int n);
int	ft_print_u(unsigned const int n);
int	ft_print_x(char format, unsigned int n);

#endif