/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 23:53:13 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/23 02:35:59 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"

static void	close_files_no_fork_redir(int *tab_fd1, int *tab_fd2, int *tab_fd3)
{
	if ((*tab_fd1) > 0)
	{
		close((*tab_fd1));
		(*tab_fd1) = -2;
	}
	if (*tab_fd2 > 0)
	{
		close((*tab_fd2));
		(*tab_fd2) = -2;
	}
	if ((*tab_fd3) > 0)
	{
		close((*tab_fd3));
		(*tab_fd3) = -2;
	}
}

static int	*check_dup_error(int **tab_fd)
{
	if ((*tab_fd)[0] < 0)
		return (close_files_no_fork_redir(&(*tab_fd)[1], &(*tab_fd)[2],
				&(*tab_fd)[3]), ft_write(2, "dup2 failed\n"), free((*tab_fd)),
			NULL);
	if ((*tab_fd)[1] < 0)
		return (close_files_no_fork_redir(&(*tab_fd)[0], &(*tab_fd)[2],
				&(*tab_fd)[3]), ft_write(2, "dup2 failed\n"), free((*tab_fd)),
			NULL);
	if ((*tab_fd)[2] < 0)
		return (close_files_no_fork_redir(&(*tab_fd)[0], &(*tab_fd)[1],
				&(*tab_fd)[3]), ft_write(2, "dup2 failed\n"), free((*tab_fd)),
			NULL);
	if ((*tab_fd)[3] < 0)
		return (close_files_no_fork_redir(&(*tab_fd)[0], &(*tab_fd)[1],
				&(*tab_fd)[2]), ft_write(2, "dup2 failed\n"), free((*tab_fd)),
			NULL);
	return ((*tab_fd));
}

static int	*no_fork_redirection(t_cmd *current)
{
	int		*tab_fd;
	t_cmd	*curr;

	tab_fd = ft_calloc(4, sizeof(int));
	if (!tab_fd)
		return (ft_write(2, "malloc failed\n"), NULL);
	curr = current;
	if (curr->last && curr->last->type == IN_FILE)
	{
		tab_fd[2] = dup(STDIN_FILENO);
		tab_fd[0] = dup2(curr->last->fd, STDIN_FILENO);
	}
	if (curr->next && curr->next->type != OUT_FILE)
		while (curr->next && curr->next->type == ARGUMENT)
			curr = curr->next;
	if (curr->next && curr->next->type == OUT_FILE)
	{
		tab_fd[3] = dup(STDOUT_FILENO);
		tab_fd[1] = dup2(curr->next->fd, STDOUT_FILENO);
	}
	return (check_dup_error(&tab_fd));
}

static int	exec_ft_cmd_exec_builtin_no_fork(t_cmd **data,
		t_exe_builtin *new_env, t_cmd *curr, int **tmp_fd)
{
	int	res;

	res = 0;
	*tmp_fd = no_fork_redirection(curr);
	if (!*tmp_fd)
		return (1);
	res = exec_ft_no_fork_builtin_exe((*data), curr, new_env, tmp_fd);
	if (reset_std_fd(*tmp_fd) == -1)
		return (free(*tmp_fd), 1);
	if (*tmp_fd)
	{
		free(*tmp_fd);
		*tmp_fd = NULL;
	}
	return (res);
}

int	exec_ft_cmd_exec_builtin(t_cmd **data, t_exe_builtin *new_env, t_cmd *curr,
		pid_t *pid)
{
	int	res;
	int	*tmp_fd;

	if (curr->fd != -3)
	{
		if (exec_ft_pipe(data, curr) == 0 || (curr->last
				&& curr->last->op == PIPE))
		{
			*pid = exec_ft_fork_builtin(data, curr, new_env, *pid);
			exec_reset_pipefd(data);
		}
		else
		{
			res = exec_ft_cmd_exec_builtin_no_fork(data, new_env, curr,
					&tmp_fd);
			(*data)->exec_cmd = (*data)->exec_cmd->next;
			return (res);
		}
	}
	(*data)->exec_cmd = (*data)->exec_cmd->next;
	return (new_env->res);
}
