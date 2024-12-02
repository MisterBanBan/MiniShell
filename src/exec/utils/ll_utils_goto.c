/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_utils_goto.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:05:51 by nkermani          #+#    #+#             */
/*   Updated: 2024/05/15 16:17:15 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "utils.h"

t_cmd	*exec_ft_go_to_last(t_cmd *data)
{
	t_cmd	*curr;

	if (!data)
		return (NULL);
	curr = data;
	while (curr->next)
		curr = curr->next;
	return (curr);
}

t_cmd	*exec_ft_go_to_first(t_cmd *data)
{
	t_cmd	*curr;

	if (!data)
		return (NULL);
	curr = data;
	while (curr->last)
		curr = curr->last;
	return (curr);
}

t_cmd	*exec_ft_go_to_next_type(t_cmd *data, enum e_type type)
{
	t_cmd	*curr;

	if (!data)
		return (NULL);
	curr = data;
	while (curr->next)
	{
		if (curr->type == type)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

t_cmd	*exec_ft_go_to_last_type(t_cmd *data, enum e_type type)
{
	t_cmd	*curr;

	if (!data)
		return (NULL);
	curr = data;
	while (curr->last)
	{
		if (curr->type == type)
			return (curr);
		curr = curr->last;
	}
	return (NULL);
}
