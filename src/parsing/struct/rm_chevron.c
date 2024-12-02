/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_chevron.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:41:45 by afavier           #+#    #+#             */
/*   Updated: 2024/06/27 10:59:41 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

static void	join_che(t_cmd *temp, t_cmd *next, t_cmd **cmd_ptr);

void	rm_che(t_cmd **cmd_ptr)
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
		if (temp->op == CHEVRON_INPUT || temp->op == CHEVRON_OUTPUT
			|| (temp->op == HERE_DOC && temp->type == OPERATOR)
			|| (temp->op == APPEND && temp->type == OPERATOR)
			|| (temp->name[0] == '"' && temp->name[1] == '"')
			|| (temp->name[0] == '\'' && temp->name[1] == '\''))
		{
			join_che(temp, next, cmd_ptr);
			if (temp)
			{
				free(temp->name);
				free(temp);
			}
		}
	}
}

static void	join_che(t_cmd *temp, t_cmd *next, t_cmd **cmd_ptr)
{
	if (temp->last != NULL)
	{
		temp->last->next = temp->next;
		if (next != NULL)
			temp->next->last = temp->last;
	}
	else
	{
		*cmd_ptr = next;
		if (next != NULL)
			next->last = NULL;
	}
}
