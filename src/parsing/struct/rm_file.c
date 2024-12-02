/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:41:50 by afavier           #+#    #+#             */
/*   Updated: 2024/07/22 23:33:40 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>

static void	join_middle(t_cmd *temp);
static void	rm_file_chev(t_cmd *temp);

void	rm_files(t_cmd **cmd_ptr)
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
		if ((temp->type == IN_FILE || temp->type == OUT_FILE)
			&& (temp->fd < 0))
		{
			join_middle(temp);
			rm_file_chev(temp);
		}
	}
}

static void	join_middle(t_cmd *temp)
{
	if (temp->last != NULL)
		temp->last->next = temp->next;
	if (temp->next != NULL)
		temp->next->last = temp->last;
}

static void	rm_file_chev(t_cmd *temp)
{
	free(temp->name);
	free(temp);
}
