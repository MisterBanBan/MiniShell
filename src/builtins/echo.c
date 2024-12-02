/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:20:22 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/22 19:19:14 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "utils.h"

void	ft_whitespace_back_to_pos(char **str)
{
	int	i;

	if (!(*str) || !str)
		return ;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] < 0)
			(*str)[i] = (*str)[i] * (-1);
		i++;
	}
}

static int	ft_echo_no_args(int fd)
{
	if (ft_printf_fd(fd, "\n") == -1)
	{
		perror("echo's ft_printf failed");
		return (-1);
	}
	return (0);
}

static int	ft_echo_print_no_option(char *args, int fd)
{
	if (ft_printf_fd(fd, "%s", args) == -1)
		return (-1);
	if (ft_printf_fd(fd, "\n") == -1)
		return (-1);
	return (0);
}

static int	ft_echo_print_option(char *args, int fd)
{
	if (args)
	{
		if (ft_printf_fd(fd, "%s", args) == -1)
			return (-1);
	}
	return (0);
}

int	ft_echo(char *args, int fd)
{
	ft_whitespace_back_to_pos(&args);
	if (!args)
		return (free(args), ft_echo_no_args(fd));
	if (!ft_strncmp(args, "-n ", 3) || !ft_strncmp(args, "-n\0", 3)
		|| !ft_strncmp(args, "-n\t", 3) || !ft_strncmp(args, "-n\n", 3)
		|| !ft_strncmp(args, "-n\v", 3) || !ft_strncmp(args, "-n\f", 3)
		|| !ft_strncmp(args, "-n\r", 3))
	{
		if (!ft_strcmp(args, "-n"))
			return (free(args), 1);
		if (ft_echo_print_option(args + 3, fd) == -1)
			return (free(args), 1);
	}
	else
	{
		if (ft_echo_print_no_option(args, fd) == -1)
			return (free(args), 1);
	}
	return (free(args), 0);
}
