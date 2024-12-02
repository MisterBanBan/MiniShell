/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:15:31 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/23 01:54:22 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"

pid_t	exec_ft_fork(t_cmd **data, t_cmd *current, t_exe_builtin *new_env,
		pid_t pid)
{
	char	*cmd;

	pid = fork();
	if (pid == -1)
	{
		ft_write(2, "fork failed\n");
		return (-1);
	}
	if (pid == 0)
	{
		signal_child();
		if (exec_ft_dup2_infile(data, current) == -1)
			ft_free_exit_child(data, new_env);
		if (exec_ft_dup2_outfile(data, current) == -1)
			ft_free_exit_child(data, new_env);
		exec_ft_close_files_children(data);
		cmd = ft_strdup((*data)->exec_cmd->cmd);
		if (!cmd)
			ft_free_exit_child(data, new_env);
		exec_free_cmd_exec(&(*data)->head);
		execve_and_exit(cmd, data, current, new_env);
	}
	return (pid);
}

pid_t	exec_ft_fork_builtin(t_cmd **data, t_cmd *current,
		t_exe_builtin *new_env, pid_t pid)
{
	char	*cmd;

	pid = fork();
	if (pid == -1)
	{
		ft_write(2, "fork failed\n");
		return (-1);
	}
	if (pid == 0)
	{
		signal_child();
		if (exec_ft_dup2_infile(data, current) == -1)
			ft_free_exit_child(data, new_env);
		if (exec_ft_dup2_outfile(data, current) == -1)
			ft_free_exit_child(data, new_env);
		exec_ft_close_files_children(data);
		cmd = ft_strdup((*data)->exec_cmd->cmd);
		if (!cmd)
			ft_free_exit_child(data, new_env);
		exec_free_cmd_exec(&(*data)->head);
		builtin_and_exit(cmd, data, current, new_env);
	}
	return (pid);
}

static int	exec_ft_no_fork_builtin_exe_args(t_cmd *data, t_cmd *current,
		t_exe_builtin *new_env)
{
	char	*args;
	int		fd;

	if (!ft_strcmp(current->name, "echo"))
	{
		fd = ft_get_fd(current);
		args = ft_get_args(current, data->exec_cmd->cmd, "echo");
		return (ft_echo(args, fd));
	}
	if (!ft_strcmp(current->name, "cd"))
	{
		args = ft_get_args(current, data->exec_cmd->cmd, "cd");
		return (ft_cd(args, &new_env));
	}
	if (!ft_strcmp(current->name, "export"))
	{
		args = ft_get_args(current, data->exec_cmd->cmd, "export");
		return (ft_export(args, &(new_env)));
	}
	if (!ft_strcmp(current->name, "unset"))
	{
		args = ft_get_args(current, data->exec_cmd->cmd, "unset");
		return (ft_unset(args, &(new_env)));
	}
	return (0);
}

int	exec_ft_no_fork_builtin_exe(t_cmd *data, t_cmd *current,
		t_exe_builtin *new_env, int **tmp_fd)
{
	char	*args;

	if (!ft_strcmp(current->name, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(current->name, "env"))
		return (ft_env(new_env));
	if (!ft_strcmp(current->name, "exit"))
	{
		args = ft_get_args(current, data->exec_cmd->cmd, "exit");
		if (!args && *tmp_fd)
		{
			if (reset_std_fd(*tmp_fd) == -1)
			{
				free(*tmp_fd);
				(*tmp_fd) = NULL;
				return (1);
			}
			free(*tmp_fd);
			*tmp_fd = NULL;
		}
		return (ft_exit(args, data, &new_env, NULL));
	}
	return (exec_ft_no_fork_builtin_exe_args(data, current, new_env));
}
