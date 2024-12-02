/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:14:22 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 05:36:20 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"

static int	exec_ft_builtin_exe_others(t_cmd *current,
		t_exe_builtin *new_env, char *builtin)
{
	char	*args;

	args = NULL;
	if (!ft_strcmp(current->name, "cd"))
	{
		args = ft_get_args(current, builtin, "cd");
		return (ft_cd(args, &new_env));
	}
	if (!ft_strcmp(current->name, "export"))
	{
		args = ft_get_args(current, builtin, "export");
		return (ft_export(args, &(new_env)));
	}
	if (!ft_strcmp(current->name, "unset"))
	{
		args = ft_get_args(current, builtin, "unset");
		return (ft_unset(args, &(new_env)));
	}
	return (0);
}

int	exec_ft_builtin_exe(t_cmd *current, t_exe_builtin *new_env,
		char *builtin)
{
	char	*args;

	args = NULL;
	if (!ft_strcmp(current->name, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(current->name, "echo"))
	{
		args = ft_get_args(current, builtin, "echo");
		return (ft_echo(args, 1));
	}
	else if (!ft_strcmp(current->name, "env"))
	{
		return (ft_env(new_env));
	}
	else if (!ft_strcmp(current->name, "exit"))
	{
		args = ft_get_args(current, builtin, "exit");
		return (ft_exit_fork(args, &new_env));
	}
	return (exec_ft_builtin_exe_others(current, new_env, builtin));
}

int	ft_get_fd(t_cmd *current)
{
	t_cmd	*curr;

	curr = current;
	if (curr->next && curr->next->type == ARGUMENT)
	{
		while (curr->next && curr->next->type == ARGUMENT)
			curr = curr->next;
	}
	if (curr->next && curr->next->type == OUT_FILE)
	{
		return (curr->next->fd);
	}
	return (1);
}
