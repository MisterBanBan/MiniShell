/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:33:10 by nkermani          #+#    #+#             */
/*   Updated: 2024/05/14 14:42:37 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

void	exec_ft_dup_last_infile(t_cmd *data)
{
	t_cmd	*ptr;

	ptr = exec_ft_go_to_last(data);
	while (ptr->last)
	{
		if (ptr->type == IN_FILE)
		{
			dup2(ptr->fd, STDIN_FILENO);
			break ;
		}
		ptr = ptr->last;
	}
}

void	exec_ft_dup_last_outfile(t_cmd *data)
{
	t_cmd	*ptr;

	ptr = exec_ft_go_to_last(data);
	while (ptr->last)
	{
		if (ptr->type == OUT_FILE)
		{
			dup2(ptr->fd, STDOUT_FILENO);
			break ;
		}
		ptr = ptr->last;
	}
}

void	exec_ft_dup_pipe(int pipefd[2], int temp_fd)
{
	dup2(temp_fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
}
