/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:10:45 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/09 03:37:34 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:19:37 by nkermani          #+#    #+#             */
/*   Updated: 2024/01/07 11:52:16 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf_fd.h"

int	ft_printf_fd(int fd, const char *format, ...)
{
	int		count;
	va_list	ap;

	if (fd < 0)
		return (0);
	va_start(ap, format);
	count = printf_parse_n_count_fd(format, &ap, fd);
	va_end(ap);
	return (count);
}

int	printf_parse_n_count_fd(const char *format, va_list *ap, int fd)
{
	int	count;

	if (!format)
		return (-1);
	count = 0;
	while (*format)
	{
		if (*(format) == '%')
		{
			if (printf_type_check_fd(format) == 1)
			{
				count += printf_type_count_fd(format, ap, fd);
				format += 2;
			}
			else if (printf_type_check_fd(format) == -1)
				return (-1);
		}
		else
		{
			count += printf_putchar_fd(*format, fd);
			format++;
		}
	}
	return (count);
}

int	printf_type_check_fd(const char *format)
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

int	printf_type_count_fd(const char *format, va_list *ap, int fd)
{
	format++;
	if (*(format) == 'c')
		return (printf_putchar_fd((char)va_arg(*ap, int), fd));
	else if (*(format) == 's')
		return (printf_putstr_fd(va_arg(*ap, char *), fd));
	else if (*(format) == 'p')
		return (printf_put_p_fd((unsigned long)va_arg(*ap, void *), fd));
	else if (*(format) == 'd')
		return (printf_putnbr_base_fd(va_arg(*ap, int), DECIMAL_BASE, fd));
	else if (*(format) == 'i')
		return (printf_putnbr_base_fd(va_arg(*ap, int), DECIMAL_BASE, fd));
	else if (*(format) == 'u')
		return (printf_putnbr_base_unsigned_fd(va_arg(*ap, unsigned int),
				DECIMAL_BASE, fd));
	else if (*(format) == 'x')
		return (printf_putnbr_base_unsigned_fd(va_arg(*ap, unsigned int),
				HEXA_LOWER_BASE, fd));
	else if (*(format) == 'X')
		return (printf_putnbr_base_unsigned_fd(va_arg(*ap, unsigned int),
				HEXA_UPPER_BASE, fd));
	else if (*(format) == '%')
		return (printf_putchar_fd('%', fd));
	else
		return (-1);
}

int	printf_strlen_fd(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return ((int)i);
}
