/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:41:08 by afavier           #+#    #+#             */
/*   Updated: 2024/06/24 13:07:15 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	append_buil(t_cmd *curr);

int	append_cmd(t_cmd **first, char *name)
{
	t_cmd	*last;
	t_cmd	*curr;

	if (!name)
		return (-1);
	curr = ft_calloc(1, sizeof(t_cmd));
	if (!curr)
		return (-1);
	curr->name = ft_strdup(name);
	if (!curr->name)
		return (free(curr), -1);
	append_buil(curr);
	if (*first == NULL)
	{
		*first = curr;
		curr->last = NULL;
		return (0);
	}
	last = *first;
	while (last->next != NULL)
		last = last->next;
	curr->last = last;
	last->next = curr;
	return (0);
}

static void	append_buil(t_cmd *curr)
{
	curr->builtin = NO_BUILTINS;
	curr->type = NO_TYPE;
	curr->op = NO_OPERATOR;
	curr->fd = -2;
	curr->pfd[0] = -2;
	curr->pfd[1] = -2;
	curr->tmpfd = -2;
	curr->quote = false;
}

void	append_type_ope_built(int builtins, int type, int operator,
		t_cmd **cmd)
{
	t_cmd	*last;

	last = *cmd;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->builtin = builtins;
	last->type = type;
	last->op = operator;
}

void	append_fd(int fd, t_cmd **cmd)
{
	t_cmd	*last;

	last = *cmd;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->fd = fd;
}

void	free_cmd_list(t_cmd **head)
{
	t_cmd	**current;
	t_cmd	*temp;

	current = &(*head);
	while ((*current))
	{
		temp = (*current);
		(*current) = (*current)->next;
		if (temp->fd > 0)
			close(temp->fd);
		free(temp->name);
		free(temp);
	}
	*head = NULL;
}
