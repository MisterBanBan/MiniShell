/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_struct_out.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:53:56 by afavier           #+#    #+#             */
/*   Updated: 2024/06/27 18:04:02 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	rm_outfile(t_cmd **next, t_cmd **temp, t_cmd **cmd);
static void	move_out(t_cmd **next, t_cmd **temp);

void	order_struct_out(t_cmd **cmd_ptr)
{
	t_cmd	*temp;
	t_cmd	*next;
	t_cmd	*cmd;

	cmd = *cmd_ptr;
	next = cmd;
	while (next != NULL)
	{
		temp = next;
		next = next->next;
		if (temp->type == OUT_FILE && (temp->next != NULL
				&& temp->next->op != PIPE))
		{
			if (next != NULL && temp->last != NULL)
				move_out(&next, &temp);
			else
			{
				rm_outfile(&next, &temp, &cmd);
				if (cmd->last != NULL)
					*cmd_ptr = cmd->last;
			}
			next = cmd;
		}
	}
}

static void	move_out(t_cmd **next, t_cmd **temp)
{
	(*next)->last = (*temp)->last;
	(*temp)->next = (*next)->next;
	if ((*next)->next != NULL)
		(*next)->next->last = (*temp);
	(*next)->next = (*temp);
	(*temp)->last = *next;
	(*next)->last->next = (*next);
}

static void	rm_outfile(t_cmd **next, t_cmd **temp, t_cmd **cmd)
{
	if ((*next) == NULL || (*next)->op == PIPE)
		return ;
	while ((*next)->next != NULL && (*next)->next->op != PIPE)
		(*next) = (*next)->next;
	if ((*next)->next == NULL)
	{
		(*next)->next = *temp;
		(*temp)->next->last = NULL;
		if ((*temp)->last == NULL)
			(*cmd) = (*temp)->next;
		(*temp)->last = (*next);
		(*temp)->next = NULL;
	}
	else
	{
		(*next)->last = (*temp)->last;
		(*temp)->next = (*next)->next;
		if ((*next)->next != NULL)
			(*next)->next->last = (*temp);
		(*next)->next = (*temp);
		(*temp)->last = *next;
		if ((*next)->last != NULL)
			(*next)->last->next = (*next);
	}
}
