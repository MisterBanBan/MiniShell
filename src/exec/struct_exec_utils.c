/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_exec_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:40:02 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/14 00:01:43 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "struct.h"
#include "utils.h"

void	ft_whitespace_to_neg(char **str)
{
	int	i;

	if (!(*str) || !str)
		return ;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == ' ' || (*str)[i] == '\t' || (*str)[i] == '\n'
			|| (*str)[i] == '\v' || (*str)[i] == '\f' || (*str)[i] == '\r')
		{
			(*str)[i] = (*str)[i] * (-1);
		}
		i++;
	}
}

static int	exec_ft_fill_last_node_cmd_loop(t_exec_cmd **first,
		t_exec_cmd **roam, t_cmd **temp, char **build)
{
	while ((*temp)->next && (*temp)->next->type == ARGUMENT)
	{
		if ((*temp)->next->quote)
			ft_whitespace_to_neg(&(*temp)->next->name);
		(*build) = ft_strjoin((*roam)->cmd, " ");
		if (!(*build))
		{
			perror("ft_strjoin error");
			return (exec_free_cmd_exec(first), free((*roam)->cmd), -1);
		}
		free((*roam)->cmd);
		(*roam)->cmd = ft_strjoin((*build), (*temp)->next->name);
		if (!(*roam)->cmd)
		{
			perror("ft_strjoin error");
			return (exec_free_cmd_exec(first), free((*build)), -1);
		}
		free((*build));
		(*temp) = (*temp)->next;
	}
	return (0);
}

void	exec_ft_fill_last_node_cmd(t_exec_cmd **first, t_cmd *curr)
{
	t_exec_cmd	*roam;
	t_cmd		*temp;
	char		*build;

	if (!first || !(*first))
		return ;
	roam = exec_ft_lstlast(*first);
	temp = NULL;
	roam->cmd = ft_strdup(curr->name);
	if (roam->cmd && curr->quote)
		ft_whitespace_to_neg(&roam->cmd);
	roam->quote = curr->quote;
	if (!roam->cmd)
	{
		perror("strdup error");
		exec_free_cmd_exec(first);
		return ;
	}
	if (curr->next)
		temp = curr;
	else
		return ;
	if (exec_ft_fill_last_node_cmd_loop(first, &roam, &temp, &build) == -1)
		return ;
}
