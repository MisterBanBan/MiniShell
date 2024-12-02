/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:59:58 by nkermani          #+#    #+#             */
/*   Updated: 2024/02/19 18:05:20 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf_fd.h"

int	printf_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) < 0)
		return (-1);
	else
		return (1);
}

int	printf_putstr_fd(char *str, int fd)
{
	if (!str)
		return (printf_putstr_fd("(null)", fd));
	if (write(fd, str, printf_strlen_fd(str)) < 0)
		return (-1);
	else
		return (printf_strlen_fd(str));
}

int	printf_putnbr_base_fd(int n, char *base, int fd)
{
	int	count;

	count = 0;
	if (n == INT_MIN)
		return (printf_putstr_fd("-2147483648", fd));
	if (n < 0)
	{
		n *= -1;
		count += printf_putchar_fd('-', fd);
	}
	if (n >= printf_strlen_fd(base))
		count += printf_putnbr_base_fd(n / printf_strlen_fd(base), base, fd);
	return (count += printf_putchar_fd(base[n % printf_strlen_fd(base)], fd));
}

int	printf_putnbr_base_unsigned_fd(unsigned long u, char *base, int fd)
{
	int	count;

	count = 0;
	if (u >= (unsigned int)printf_strlen_fd(base))
		count += printf_putnbr_base_unsigned_fd(u
				/ (unsigned int)printf_strlen_fd(base), base, fd);
	return (count += printf_putchar_fd(base[u % printf_strlen_fd(base)], fd));
}

int	printf_put_p_fd(unsigned long p, int fd)
{
	int	count;

	if (!p)
		return (printf_putstr_fd("(nil)", fd));
	if (p == ULONG_MAX)
		return (printf_putstr_fd("0xffffffffffffffff", fd));
	count = printf_putstr_fd("0x", fd);
	if (p >= 16)
		count += printf_putnbr_base_unsigned_fd((unsigned long)p / 16,
				HEXA_LOWER_BASE, fd);
	return (count += printf_putchar_fd(HEXA_LOWER_BASE[(unsigned long)p % 16],
			fd));
}
