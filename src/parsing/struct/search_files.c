/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:41:16 by afavier           #+#    #+#             */
/*   Updated: 2024/07/17 00:12:43 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	files_out_fonc(t_cmd **temp, t_cmd **last_open_close,
				int *files_out);
static int	files_in_fonc(t_cmd **temp, t_cmd **last_open_in, int *files_in);
static void	here_infile(int *files_in, t_cmd **last_open_in, t_cmd *temp);
static void	files_in_out(t_cmd *temp, int *files_in, int *files_out);

int	search_files(t_cmd **cmd, int res, int files_in, int files_out)
{
	t_cmd	*temp;
	t_cmd	*last_open_in;
	t_cmd	*last_open_close;
	int		i;

	temp = *cmd;
	i = 0;
	while (temp != NULL)
	{
		if (temp->name[0] == '$' && temp->name[1] == '?')
			dollars_question(temp, res);
		if (temp->type == IN_FILE && temp->op == HERE_DOC)
			here_infile(&files_in, &last_open_in, temp);
		if (temp->type == IN_FILE && temp->fd == -2)
			i = files_in_fonc(&temp, &last_open_in, &files_in);
		if (temp->type == OUT_FILE && temp->fd == -2)
			i = files_out_fonc(&temp, &last_open_close, &files_out);
		next_pipe(&temp, &i);
		files_in_out(temp, &files_in, &files_out);
		if (temp != NULL)
			temp = temp->next;
	}
	return (0);
}

static void	here_infile(int *files_in, t_cmd **last_open_in, t_cmd *temp)
{
	if (*files_in == 0)
	{
		*last_open_in = temp;
		*files_in = 1;
	}
	else
	{
		close((*last_open_in)->fd);
		(*last_open_in)->fd = -2;
		*last_open_in = temp;
	}
}

static int	files_in_fonc(t_cmd **temp, t_cmd **last_open_in, int *files_in)
{
	if (*files_in == 0)
	{
		*last_open_in = *temp;
		(*temp)->fd = open_files((*temp)->name);
		if ((*temp)->fd == -1)
			return (-1);
		*files_in = 1;
	}
	else
	{
		(*temp)->fd = open_files((*temp)->name);
		if ((*last_open_in)->fd > 0)
		{
			close((*last_open_in)->fd);
			(*last_open_in)->fd = -2;
		}
		if ((*temp)->fd == -1)
			return (-1);
		*last_open_in = *temp;
	}
	return (0);
}

static void	files_in_out(t_cmd *temp, int *files_in, int *files_out)
{
	if (temp != NULL && temp->op == PIPE)
	{
		*files_in = 0;
		*files_out = 0;
	}
}

static int	files_out_fonc(t_cmd **temp, t_cmd **last_open_close,
		int *files_out)
{
	if (*files_out == 0)
	{
		*last_open_close = *temp;
		if ((*temp)->op == APPEND)
			(*temp)->fd = open_files_append((*temp)->name);
		else
			(*temp)->fd = open_files_out((*temp)->name);
		if ((*temp)->fd < 0)
			return (-1);
		*files_out = 1;
	}
	else
	{
		if (files_ou_fonc_after(temp, last_open_close) == -1)
			return (-1);
	}
	return (0);
}
