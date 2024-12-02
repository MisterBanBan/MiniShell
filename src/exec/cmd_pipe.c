/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 23:41:13 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/23 00:44:34 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"

int	exec_ft_pipe(t_cmd **data, t_cmd *current)
{
	t_cmd	*roam;

	if (!data)
		return (-1);
	roam = current;
	while (roam)
	{
		if (roam->op == PIPE)
		{
			if (pipe((*data)->pfd) == -1)
			{
				perror("pipe failed");
				return (-1);
			}
			return (0);
		}
		roam = roam->next;
	}
	return (-1);
}
