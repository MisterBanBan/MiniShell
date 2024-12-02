/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:36:12 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 05:36:47 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"

void	builtin_and_exit(char *cmd, t_cmd **data, t_cmd *current,
		t_exe_builtin *new_env)
{
	int	res;

	res = exec_ft_builtin_exe(current, new_env, cmd);
	ft_free_break(&new_env, NULL);
	free_cmd_list(data);
	if (cmd)
	{
		free(cmd);
		cmd = NULL;
	}
	exit(res);
}

void	execve_and_exit(char *cmd, t_cmd **data, t_cmd *current,
		t_exe_builtin *new_env)
{
	int	res;

	res = exec_exec_ft_execve(cmd, current, new_env->envp_b);
	ft_free_break(&new_env, NULL);
	free_cmd_list(data);
	free(cmd);
	exit(res);
}

void	ft_free_exit_child(t_cmd **data, t_exe_builtin *new_env)
{
	exec_ft_close_files_children(data);
	exec_free_cmd_exec(&(*data)->head);
	ft_free_break(&new_env, NULL);
	free_cmd_list(data);
	exit(1);
}
