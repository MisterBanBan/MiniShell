/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:52:27 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/23 02:34:17 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"
#include <signal.h>

static int	ft_wait_pid(pid_t pid, t_exe_builtin **new_env)
{
	int	status;
	int	pid2;
	int	sig;

	pid2 = wait(&status);
	while (pid2 > 0)
	{
		if (pid2 == pid)
		{
			if (WIFEXITED(status) > 0)
			{
				(*new_env)->res = (WEXITSTATUS(status));
			}
			else if (WIFSIGNALED(status) > 0)
				ft_wait_sig_part(&sig, &(*new_env)->res, status);
		}
		pid2 = wait(&status);
	}
	return ((*new_env)->res);
}

static void	exec_ft_cmd_exec_command(t_cmd **data, t_exe_builtin *new_env,
		t_cmd *curr, pid_t *pid)
{
	if (curr->fd != -3)
	{
		exec_ft_pipe(data, curr);
		*pid = exec_ft_fork(data, curr, new_env, *pid);
		exec_reset_pipefd(data);
	}
	(*data)->exec_cmd = (*data)->exec_cmd->next;
}

int	exec_ft_cmd_exec(t_cmd *data, t_exe_builtin *new_env)
{
	t_cmd		*curr;
	t_exec_cmd	*first;
	pid_t		pid;

	signal_wait();
	if (!data)
		return (ft_write(2, "exec_ft_cmd_exec: data == NULL\n"), -1);
	pid = -2;
	curr = data;
	first = data->exec_cmd;
	data->head = first;
	while (curr != NULL)
	{
		if (curr->type == BUILTIN)
			new_env->res = exec_ft_cmd_exec_builtin(&data, new_env, curr, &pid);
		else if (curr->type == COMMAND)
			exec_ft_cmd_exec_command(&data, new_env, curr, &pid);
		curr = curr->next;
	}
	if (data->tmpfd != -2)
		close(data->tmpfd);
	data->exec_cmd = first;
	ft_wait_pid(pid, &new_env);
	return (new_env->res);
}
