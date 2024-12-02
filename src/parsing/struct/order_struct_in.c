/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_struct_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:41:30 by afavier           #+#    #+#             */
/*   Updated: 2024/07/22 18:25:16 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	rm_infile(t_cmd **next, t_cmd **temp, t_cmd **cmd);
static void	move_infile(t_cmd **next, t_cmd **temp, t_cmd **cmd);

void	order_struct_in(t_cmd **cmd_ptr, t_cmd *temp, t_cmd	*next, t_cmd *cmd)
{
	cmd = *cmd_ptr;
	next = cmd;
	while (next != NULL)
	{
		temp = next;
		next = next->next;
		cmd = *cmd_ptr;
		if (temp->type == IN_FILE && (temp->last != NULL
				&& temp->last->op != PIPE))
		{
			rm_infile(&next, &temp, &cmd);
			if (cmd->last != NULL)
				*cmd_ptr = cmd->last;
			next = cmd;
		}
		else if (temp->type == COMMAND && temp->last != NULL
			&& temp->last->type != IN_FILE && temp->last->op != PIPE)
		{
			move_infile(&next, &temp, &cmd);
			if (cmd->last != NULL)
				*cmd_ptr = cmd->last;
			next = cmd;
		}
	}
}

static void	rm_infile(t_cmd **next, t_cmd **temp, t_cmd **cmd)
{
	if ((*temp)->next != NULL)
	{
		(*next)->last = (*temp)->last;
		(*temp)->last->next = *next;
	}
	else
	{
		(*temp)->last->next = NULL;
	}
	if ((*temp)->last->last != NULL)
	{
		(*temp)->next = (*temp)->last;
		(*temp)->last->last->next = (*temp);
		(*temp)->last = (*temp)->last->last;
		(*temp)->next->last = (*temp);
	}
	else
	{
		(*temp)->last = NULL;
		(*temp)->next = *cmd;
		(*cmd)->last = (*temp);
	}
}

static void	move_infile(t_cmd **next, t_cmd **temp, t_cmd **cmd)
{
	if ((*temp)->next != NULL)
	{
		(*next)->last = (*temp)->last;
		(*temp)->last->next = *next;
	}
	else
		(*temp)->last->next = NULL;
	if ((*temp)->last->last != NULL)
	{
		(*temp)->next = (*temp)->last;
		(*temp)->last->last->next = (*temp);
		(*temp)->last = (*temp)->last->last;
	}
	else
	{
		(*temp)->last = NULL;
		(*temp)->next = *cmd;
		(*cmd)->last = (*temp);
	}
}
