/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:42:07 by afavier           #+#    #+#             */
/*   Updated: 2024/07/23 02:08:16 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>

static void	define_file(t_cmd *temp);

void	define_struct(t_cmd **cmd)
{
	t_cmd	*temp;
	int		cmdd;

	cmdd = 0;
	temp = *cmd;
	while (temp != NULL)
	{
		if (cmdd == 0 && (temp->type == COMMAND || temp->type == BUILTIN))
			cmdd = 1;
		else if (cmdd == 1 && (temp->type == COMMAND || temp->type == BUILTIN)
			&& temp->last->op != PIPE)
		{
			if (temp->type == COMMAND || temp->type == BUILTIN)
				temp->type = ARGUMENT;
		}
		else if (temp->type == OPERATOR)
		{
			define_file(temp);
			if (temp->op == PIPE)
				cmdd = 0;
		}
		temp = temp->next;
	}
}

static void	define_file(t_cmd *temp)
{
	if (temp->op == CHEVRON_INPUT)
	{
		if (temp->next != NULL)
			temp->next->type = IN_FILE;
	}
	else if (temp->op == CHEVRON_OUTPUT)
	{
		if (temp->next != NULL)
			temp->next->type = OUT_FILE;
	}
	else if (temp->op == HERE_DOC)
	{
		if (temp->next != NULL)
			temp->next->op = HERE_DOC;
	}
	else if (temp->op == APPEND)
	{
		if (temp->next != NULL)
		{
			temp->next->type = OUT_FILE;
			temp->next->op = APPEND;
		}
	}
}

void	dollars_question(t_cmd *temp, int res)
{
	free(temp->name);
	temp->name = ft_itoa(res);
}

int	next_pipe(t_cmd **temp, int *i)
{
	if (*i == -1)
	{
		while ((*temp)->last != NULL && (*temp)->last->op != PIPE)
		{
			if ((*temp)->fd > 0)
				close((*temp)->fd);
			(*temp)->fd = -3;
			*temp = (*temp)->last;
		}
		while (*temp != NULL && (*temp)->op != PIPE)
		{
			if ((*temp)->fd > 0)
				close((*temp)->fd);
			(*temp)->fd = -3;
			*temp = (*temp)->next;
		}
		if (*temp != NULL && (*temp)->op == PIPE)
			(*temp)->fd = -3;
		if (*temp == NULL)
			return (0);
		*i = 0;
	}
	return (0);
}

int	files_ou_fonc_after(t_cmd **temp, t_cmd **last_open_close)
{
	if ((*temp)->op == APPEND)
		(*temp)->fd = open_files_append((*temp)->name);
	else
		(*temp)->fd = open_files_out((*temp)->name);
	if ((*temp)->fd < 0)
		return (-1);
	if ((*last_open_close)->fd > 0)
	{
		close((*last_open_close)->fd);
		(*last_open_close)->fd = -2;
	}
	*last_open_close = *temp;
	return (0);
}
