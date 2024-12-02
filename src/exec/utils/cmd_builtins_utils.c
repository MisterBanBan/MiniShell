/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtins_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 01:51:38 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/23 01:56:04 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"

int	reset_std_fd(int *tmp_fd)
{
	if (tmp_fd[0] > 0)
		if (dup2(tmp_fd[2], tmp_fd[0]) == -1)
			return (ft_write(2, "dup2 failed\n"), -1);
	if (tmp_fd[2] > 0)
	{
		if (close(tmp_fd[2]))
		{
			tmp_fd[2] = 0;
			return (ft_write(2, "close failed\n"), -1);
		}
	}
	if (tmp_fd[1] > 0)
		if (dup2(tmp_fd[3], tmp_fd[1]) == -1)
			return (ft_write(2, "dup2 failed\n"), -1);
	if (tmp_fd[3] > 0)
	{
		if (close(tmp_fd[3]))
		{
			tmp_fd[3] = 0;
			return (ft_write(2, "close failed\n"), -1);
		}
	}
	return (0);
}
