/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quote_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:53 by afavier           #+#    #+#             */
/*   Updated: 2024/07/17 00:47:09 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	malloc_start(int i, char **start, t_cmd *temp)
{
	if (i > 0)
	{
		*start = ft_calloc(i + 1, sizeof(char));
		if (!*start)
			return (-1);
		ft_strcpy(*start, temp->name, i);
	}
	return (0);
}

int	if_tab_split_null(t_cmd *temp, char **tab_split, int *j, char *start)
{
	if (tab_split[*j] == NULL)
	{
		free(temp->name);
		temp->name = ft_strdup(start);
		if (!temp->name)
			return (free(start), -1);
		free(start);
		start = NULL;
	}
	return (0);
}

int	check_pipe_after(t_input *get_inp, int i, int len)
{
	if (get_inp->input[i] == '|')
	{
		i++;
		while (get_inp->input[i])
		{
			if (get_inp->input[i] == '|')
				break ;
			if (get_inp->input[i] == '_' || (get_inp->input[i] >= 'a'
					&& get_inp->input[i] <= 'z') || (get_inp->input[i] >= 'A'
					&& get_inp->input[i] <= 'Z') || (get_inp->input[i] == '"')
				|| (get_inp->input[i] == '\''))
				len++;
			i++;
		}
		if (len == 0)
			return (-1);
	}
	return (0);
}

void	check_quote_synthax(t_input *get_input, size_t *i)
{
	char	quote;

	quote = get_input->input[(*i)++];
	while (get_input->input[(*i)] && get_input->input[(*i)] != quote)
		(*i)++;
}
