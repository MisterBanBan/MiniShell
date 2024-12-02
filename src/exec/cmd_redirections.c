/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:16:50 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/23 01:37:41 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"

static int	exec_ft_dup2_infile_pipe(t_cmd **data)
{
	if ((*data)->tmpfd > 0 && (*data)->pfd[0] > 0)
	{
		if (close((*data)->pfd[0]) == -1)
			return (-1);
		(*data)->pfd[0] = dup((*data)->tmpfd);
		if ((*data)->pfd[0] == -1)
			return (-1);
		if (dup2((*data)->pfd[0], STDIN_FILENO) == -1)
			return (-1);
	}
	else
	{
		if ((*data)->tmpfd > 0 && (dup2((*data)->tmpfd, STDIN_FILENO) == -1))
			return (-1);
	}
	return (0);
}

int	exec_ft_dup2_infile(t_cmd **data, t_cmd *current)
{
	t_cmd	*curr;

	curr = current;
	if (curr->last && curr->last->type == IN_FILE)
	{
		if (dup2(curr->last->fd, STDIN_FILENO) == -1)
			return (-1);
		return (0);
	}
	if (curr->last && (curr->last->op == PIPE))
	{
		if (curr->last->fd == -3)
			return (0);
		if (exec_ft_dup2_infile_pipe(data) == -1)
			return (-1);
	}
	else
		return (0);
	return (0);
}

static t_cmd	*exec_ft_dup2_outfile_pass(t_cmd *current)
{
	t_cmd	*curr;

	curr = current;
	if (curr->next && curr->next->type == ARGUMENT)
	{
		while (curr->next && curr->next->type == ARGUMENT)
			curr = curr->next;
	}
	return (curr);
}

int	exec_ft_dup2_outfile(t_cmd **data, t_cmd *current)
{
	t_cmd	*curr;

	curr = exec_ft_dup2_outfile_pass(current);
	if (curr->next && curr->next->type == OUT_FILE)
	{
		if (dup2(curr->next->fd, STDOUT_FILENO) == -1)
			return (-1);
		return (0);
	}
	if (curr->next && curr->next->op == PIPE)
	{
		if (curr->next->fd == -3)
			return (0);
		if (dup2((*data)->pfd[1], STDOUT_FILENO) == -1)
			return (-1);
		return (0);
	}
	else
		return (0);
}

int	exec_reset_pipefd(t_cmd **data)
{
	if ((*data)->tmpfd != -2)
	{
		if (close((*data)->tmpfd) == -1)
			perror("reset close tmpfd");
		(*data)->tmpfd = -2;
	}
	if ((*data)->pfd[0] != -2)
	{
		(*data)->tmpfd = dup((*data)->pfd[0]);
		if ((*data)->tmpfd == -1)
			perror("reset dup failed");
		if (close((*data)->pfd[0]) == -1)
			perror("reset close pfd0 failed");
		(*data)->pfd[0] = -2;
	}
	if ((*data)->pfd[1] != -2)
	{
		if (close((*data)->pfd[1]) == -1)
			perror("reset close pfd1 failed");
		(*data)->pfd[1] = -2;
	}
	return (0);
}
