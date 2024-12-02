/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:49:48 by nkermani          #+#    #+#             */
/*   Updated: 2024/02/19 16:49:58 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define DECIMAL_BASE "0123456789"
# define HEXA_UPPER_BASE "0123456789ABCDEF"
# define HEXA_LOWER_BASE "0123456789abcdef"

int	ft_printf_fd(int fd, const char *format, ...);
int	printf_parse_n_count_fd(const char *format, va_list *ap, int fd);
int	printf_type_check_fd(const char *format);
int	printf_type_count_fd(const char *format, va_list *ap, int fd);
int	printf_putchar_fd(char c, int fd);
int	printf_putstr_fd(char *str, int fd);
int	printf_strlen_fd(char *str);
int	printf_putnbr_base_fd(int n, char *base, int fd);
int	printf_put_p_fd(unsigned long p, int fd);
int	printf_putnbr_base_unsigned_fd(unsigned long u, char *base, int fd);

#endif