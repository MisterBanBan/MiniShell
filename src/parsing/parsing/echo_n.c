/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:25:24 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/12 22:01:14 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>

static int	option_n(char *string);
static int	rm_n(t_cmd *next, int rm);

void	neg(t_cmd **cmd_ptr)
{
	t_cmd	*next;
	t_cmd	*cmd;
	int		i;

	cmd = *cmd_ptr;
	next = cmd;
	i = 0;
	while (next != NULL)
	{
		while (next->name[i])
		{
			if (next->name[i] < 0)
				next->name[i] = next->name[i] * (-1);
			i++;
		}
		i = 0;
		next = next->next;
	}
}

int	echo_n(t_cmd **cmd_ptr, int i)
{
	t_cmd	*next;
	t_cmd	*cmd;

	cmd = *cmd_ptr;
	next = cmd;
	while (next != NULL)
	{
		while (next->name[i])
		{
			if (next->name[i] < 0)
				next->name[i] = next->name[i] * (-1);
			i++;
		}
		i = 0;
		if (ft_strcmp(next->name, "echo") == 0)
		{
			if (next->next != NULL)
				next = next->next;
			if (rm_n(next, 0) == -1)
				return (-1);
		}
		if (next != NULL)
			next = next->next;
	}
	return (0);
}

static int	rm_n(t_cmd *next, int rm)
{
	t_cmd	*temp;

	while (next != NULL && (option_n(next->name) == 0))
	{
		rm++;
		temp = next;
		free(temp->name);
		temp->name = ft_strdup("-n");
		if (!temp->name)
			return (-1);
		next = next->next;
		if (rm > 1)
		{
			temp->last->next = temp->next;
			if (temp->next != NULL)
				temp->next->last = temp->last;
			if (temp)
			{
				free(temp->name);
				free(temp);
			}
		}
	}
	return (0);
}

static int	option_n(char *string)
{
	int	i;

	i = 1;
	if (!string || string[0] != '-')
		return (-1);
	while (string[i] == 'n')
		i++;
	if (string[i])
		return (-1);
	return (0);
}
