/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:49:00 by nkermani          #+#    #+#             */
/*   Updated: 2024/03/09 21:40:14 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	ap;

	va_start(ap, format);
	count = printf_parse_n_count(format, &ap);
	va_end(ap);
	return (count);
}

int	printf_parse_n_count(const char *format, va_list *ap)
{
	int	count;

	if (!format)
		return (-1);
	count = 0;
	while (*format)
	{
		if (*(format) == '%')
		{
			if (printf_type_check(format) == 1)
			{
				count += printf_type_count(format, ap);
				format += 2;
			}
			else if (printf_type_check(format) == -1)
				return (-1);
		}
		else
		{
			count += printf_putchar(*format);
			format++;
		}
	}
	return (count);
}

int	printf_type_check(const char *format)
{
	format++;
	if (*format == 'c' || *format == 's' || *format == 'p' || *format == 'd'
		|| *format == 'i' || *format == 'u' || *format == 'x' || *format == 'X'
		|| *format == '%')
		return (1);
	else if (*format == '\0')
		return (-1);
	else
		return (0);
}

int	printf_type_count(const char *format, va_list *ap)
{
	format++;
	if (*(format) == 'c')
		return (printf_putchar((char)va_arg(*ap, int)));
	else if (*(format) == 's')
		return (printf_putstr(va_arg(*ap, char *)));
	else if (*(format) == 'p')
		return (printf_put_p((unsigned long)va_arg(*ap, void *)));
	else if (*(format) == 'd')
		return (printf_putnbr_base(va_arg(*ap, int), DECIMAL_BASE));
	else if (*(format) == 'i')
		return (printf_putnbr_base(va_arg(*ap, int), DECIMAL_BASE));
	else if (*(format) == 'u')
		return (printf_putnbr_base_unsigned(va_arg(*ap, unsigned int),
				DECIMAL_BASE));
	else if (*(format) == 'x')
		return (printf_putnbr_base_unsigned(va_arg(*ap, unsigned int),
				HEXA_LOWER_BASE));
	else if (*(format) == 'X')
		return (printf_putnbr_base_unsigned(va_arg(*ap, unsigned int),
				HEXA_UPPER_BASE));
	else if (*(format) == '%')
		return (printf_putchar('%'));
	else
		return (-1);
}

int	printf_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return ((int)i);
}
