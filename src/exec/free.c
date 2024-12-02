/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:06:41 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/17 00:48:58 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "struct.h"

void	exec_ft_free_tab(char **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void	exec_free_cmd_exec(t_exec_cmd **cmd)
{
	t_exec_cmd	*temp;
	t_exec_cmd	*next;

	if (!cmd || !(*cmd))
		return ;
	else
		temp = *cmd;
	while (temp)
	{
		next = temp->next;
		if (temp->cmd)
			free(temp->cmd);
		free(temp);
		temp = next;
	}
	*cmd = NULL;
}

void	ft_free_get_input(t_input **get_input)
{
	if ((*get_input))
	{
		if ((*get_input)->input)
		{
			free((*get_input)->input);
			(*get_input)->input = NULL;
		}
		free((*get_input));
		(*get_input) = NULL;
	}
}

void	ft_free_usual(char **line, t_input **get_input)
{
	if ((*line))
	{
		free((*line));
		(*line) = NULL;
	}
	if ((*get_input))
	{
		if ((*get_input)->input)
		{
			free((*get_input)->input);
			(*get_input)->input = NULL;
		}
		free((*get_input));
		(*get_input) = NULL;
	}
}

void	ft_free_break(t_exe_builtin **new_env, t_cmd **cmd)
{
	if (new_env && (*new_env))
	{
		if ((*new_env)->cwd)
		{
			free((*new_env)->cwd);
			(*new_env)->cwd = NULL;
		}
		if ((*new_env)->oldpwd)
		{
			free((*new_env)->oldpwd);
			(*new_env)->oldpwd = NULL;
		}
		if ((*new_env)->name_val)
		{
			exec_ft_free_tab((*new_env)->name_val[0]);
			exec_ft_free_tab((*new_env)->name_val[1]);
			free((*new_env)->name_val);
		}
		if ((*new_env)->envp_b)
			exec_ft_free_tab((*new_env)->envp_b);
		free((*new_env));
		(*new_env) = NULL;
	}
	if (cmd && (*cmd))
		free_cmd_list(cmd);
}
