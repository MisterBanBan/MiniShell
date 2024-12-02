/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_space_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:46:19 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/17 00:46:19 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	if_space_dollars(t_input *get_input, size_t *i);

int	space_append(t_input *get_input, size_t *i)
{
	if (if_space(get_input, i) == -1)
		return (-1);
	if (if_pipe_space(get_input, i) == -1)
		return (-1);
	if (get_input->input[*i])
		(*i)++;
	if (get_input->input[*i] && (get_input->input[*i] == '|'
			|| (get_input->input[*i] == '>' && get_input->input[*i] != '>')
			|| (get_input->input[*i] == '<' && get_input->input[*i] != '<')))
	{
		if (get_input->input[*i])
			(*i)++;
	}
	else
	{
		if (get_input->input[*i] && get_input->input[*i + 1])
			*i = *i + 2;
	}
	return (0);
}

int	if_space(t_input *get_input, size_t *i)
{
	if (get_input->input[*i] == '>' && get_input->input[*i + 1] == '>')
	{
		if (append_space_chevron(get_input, " >> ", *i, 4) == -1)
			return (-1);
	}
	else if (get_input->input[*i] == '<' && get_input->input[*i + 1] == '<')
	{
		if (append_space_chevron(get_input, " << ", *i, 4) == -1)
			return (-1);
	}
	else if (get_input->input[*i] == '>')
	{
		if (append_space_chevron(get_input, " > ", *i, 3) == -1)
			return (-1);
	}
	else if (get_input->input[*i] == '<')
	{
		if (append_space_chevron(get_input, " < ", *i, 3) == -1)
			return (-1);
	}
	if (if_space_dollars(get_input, i) == -1)
		return (-1);
	return (0);
}

static int	if_space_dollars(t_input *get_input, size_t *i)
{
	if (get_input->input[*i] == '$' && get_input->input[*i + 1] == '?')
	{
		if (append_space_chevron(get_input, " $? ", *i, 4) == -1)
			return (-1);
	}
	return (0);
}
