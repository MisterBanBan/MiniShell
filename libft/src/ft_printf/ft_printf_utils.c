/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:59:58 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/23 01:59:18 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	printf_putchar(char c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	else
		return (1);
}

int	printf_putstr(char *str)
{
	if (!str)
		return (printf_putstr("(null)"));
	if (write(1, str, printf_strlen(str)) < 0)
		return (-1);
	else
		return (printf_strlen(str));
}

int	printf_putnbr_base(int n, char *base)
{
	int	count;

	count = 0;
	if (n == INT_MIN)
		return (printf_putstr("-2147483648"));
	if (n < 0)
	{
		n *= -1;
		count += printf_putchar('-');
	}
	if (n >= printf_strlen(base))
		count += printf_putnbr_base(n / printf_strlen(base), base);
	return (count += printf_putchar(base[n % printf_strlen(base)]));
}

int	printf_putnbr_base_unsigned(unsigned long u, char *base)
{
	int	count;

	count = 0;
	if (u >= (unsigned int)printf_strlen(base))
		count += printf_putnbr_base_unsigned(u
				/ (unsigned int)printf_strlen(base), base);
	return (count += printf_putchar(base[u % printf_strlen(base)]));
}

int	printf_put_p(unsigned long p)
{
	int	count;

	if (!p)
		return (printf_putstr("(nil)"));
	if (p == ULONG_MAX)
		return (printf_putstr("0xffffffffffffffff"));
	count = printf_putstr("0x");
	if (p >= 16)
		count += printf_putnbr_base_unsigned((unsigned long)p / 16,
				HEXA_LOWER_BASE);
	return (count += printf_putchar(HEXA_LOWER_BASE[(unsigned long)p % 16]));
}
