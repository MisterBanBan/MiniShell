/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:23:20 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 23:19:38 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "utils.h"

static void	exec_ft_close_files_utils(t_cmd **data)
{
	if ((*data)->pfd[0] != -2)
	{
		if (close((*data)->pfd[0]) == -1)
			perror("children close pfd0");
		(*data)->pfd[0] = -2;
	}
	if ((*data)->pfd[1] != -2)
	{
		if (close((*data)->pfd[1]) == -1)
			perror("children close pfd1");
		(*data)->pfd[1] = -2;
	}
	if ((*data)->tmpfd != -2)
	{
		if (close((*data)->tmpfd) == -1)
			perror("children close tmpfd");
		(*data)->tmpfd = -2;
	}
}

int	exec_ft_close_files(t_cmd *data)
{
	t_cmd	*curr;

	if (!data)
	{
		ft_write(2, "exec_ft_close_files: data == NULL\n");
		return (-1);
	}
	curr = exec_ft_go_to_first(data);
	while (curr)
	{
		if ((curr->type == IN_FILE) && (curr->fd > 0))
		{
			if (close(curr->fd) == -1)
				perror("parent close infile");
			curr->fd = -2;
		}
		if ((curr->type == OUT_FILE) && (curr->fd > 0))
		{
			if (close(curr->fd) == -1)
				perror("parent close outfile");
			curr->fd = -2;
		}
		curr = curr->next;
	}
	return (0);
}

int	exec_ft_close_files_children(t_cmd **data)
{
	t_cmd	*curr;

	exec_ft_close_files_utils(data);
	curr = *data;
	while (curr)
	{
		if ((curr->type == IN_FILE) && (curr->fd > 0))
		{
			if (close(curr->fd) == -1)
				perror("children close infile");
			curr->fd = -2;
		}
		if ((curr->type == OUT_FILE) && (curr->fd > 0))
		{
			if (close(curr->fd) == -1)
				perror("children close outfile");
			curr->fd = -2;
		}
		curr = curr->next;
	}
	return (0);
}
