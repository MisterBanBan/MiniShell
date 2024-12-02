/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:21:04 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/12 05:08:06 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "struct.h"
#include "utils.h"

t_exec_cmd	*exec_ft_fill_struct(t_cmd *data)
{
	t_exec_cmd	*cmd_tab;
	t_cmd		*curr;
	t_exec_cmd	*new;

	if (!data)
		return (NULL);
	cmd_tab = NULL;
	curr = data;
	new = NULL;
	while (curr)
	{
		if (curr->type == COMMAND || curr->type == BUILTIN)
		{
			new = exec_ft_lstnew();
			if (!new)
			{
				exec_free_cmd_exec(&cmd_tab);
				return (NULL);
			}
			exec_ft_lstadd_back(&cmd_tab, new);
			exec_ft_fill_last_node_cmd(&cmd_tab, curr);
		}
		curr = curr->next;
	}
	return (cmd_tab);
}

t_exec_cmd	*exec_ft_lstnew(void)
{
	t_exec_cmd	*tmp;

	tmp = (t_exec_cmd *)malloc(sizeof(t_exec_cmd));
	if (!(tmp))
		return (NULL);
	tmp->cmd = NULL;
	tmp->next = NULL;
	return (tmp);
}

t_exec_cmd	*exec_ft_lstlast(t_exec_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	exec_ft_lstadd_back(t_exec_cmd **lst, t_exec_cmd *new_node)
{
	t_exec_cmd	*last;

	if (!(lst) || !(new_node))
		return ;
	if (!(*lst))
	{
		*lst = new_node;
		return ;
	}
	last = exec_ft_lstlast(*lst);
	last->next = new_node;
}
