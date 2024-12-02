/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:12:07 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 23:20:55 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "struct.h"
#include "utils.h"

static bool	direct_access_cmd(char *cmd);
static int	ft_cmd_check(t_cmd *data);

void	after_split_back_to_pos_char(char ***tab)
{
	int	i;
	int	j;

	i = 0;
	if (!(*tab) || !tab)
		return ;
	while ((*tab)[i])
	{
		j = 0;
		while ((*tab)[i][j])
		{
			if ((*tab)[i][j] < 0)
				(*tab)[i][j] = (*tab)[i][j] * (-1);
			j++;
		}
		i++;
	}
}

int	exec_ft_exec(t_cmd **data, t_exe_builtin **new_env)
{
	ft_cmd_check(*data);
	(*new_env)->res = exec_ft_cmd_exec(*data, *new_env);
	exec_ft_close_files(*data);
	return (0);
}

static bool	direct_access_cmd(char *cmd)
{
	char	**cmd_tab;

	cmd_tab = ft_split(cmd, ' ');
	if (!cmd_tab)
		return (true);
	after_split_back_to_pos_char(&cmd_tab);
	if (!cmd_tab[0])
	{
		exec_ft_free_tab(cmd_tab);
		return (true);
	}
	if (access(cmd_tab[0], F_OK | X_OK) == 0)
	{
		exec_ft_free_tab(cmd_tab);
		return (false);
	}
	exec_ft_free_tab(cmd_tab);
	return (true);
}

static int	ft_cmd_check(t_cmd *data)
{
	t_cmd		*curr;
	t_exec_cmd	*roam;

	if (!data)
	{
		ft_write(2, "ft_cmd_check: data == NULL\n");
		return (-1);
	}
	roam = data->exec_cmd;
	curr = data;
	while (curr)
	{
		if (curr->type == COMMAND)
		{
			curr->err = direct_access_cmd(roam->cmd);
			roam = roam->next;
		}
		curr = curr->next;
	}
	return (0);
}
