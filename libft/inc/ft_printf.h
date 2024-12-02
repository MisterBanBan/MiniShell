/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:11:38 by nkermani          #+#    #+#             */
/*   Updated: 2023/12/03 21:22:13 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define DECIMAL_BASE "0123456789"
# define HEXA_UPPER_BASE "0123456789ABCDEF"
# define HEXA_LOWER_BASE "0123456789abcdef"

int	ft_printf(const char *format, ...);
int	printf_parse_n_count(const char *format, va_list *ap);
int	printf_type_check(const char *format);
int	printf_type_count(const char *format, va_list *ap);
int	printf_putchar(char c);
int	printf_putstr(char *str);
int	printf_strlen(char *str);
int	printf_putnbr_base(int n, char *base);
int	printf_put_p(unsigned long p);
int	printf_putnbr_base_unsigned(unsigned long u, char *base);

#endif