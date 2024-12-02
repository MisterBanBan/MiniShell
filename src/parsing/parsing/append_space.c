/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:50:11 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 23:25:36 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static int	start_append(char **temp, size_t start, t_input *get_input,
		char *append)
{
	char	*tep;

	if (start == 0)
	{
		free(*temp);
		(*temp) = ft_strdup(append);
		if (!(*temp))
			return (ft_write(2, "Error malloc"), -1);
	}
	else
	{
		ft_strcpy((*temp), get_input->input, start);
		tep = ft_strjoin((*temp), append);
		if (!tep)
			return (ft_write(2, "Error malloc"), -1);
		free(*temp);
		*temp = ft_strdup(tep);
		free(tep);
		if (!*temp)
			return (-1);
	}
	return (0);
}

static int	end_append(char **temp, size_t start, t_input *get_input)
{
	char	*tep;

	tep = ft_strjoin((*temp), &get_input->input[start + 1]);
	if (!tep)
	{
		ft_write(2, "Error malloc");
		return (-1);
	}
	free(*temp);
	*temp = tep;
	(*temp)[ft_strlen(*temp)] = '\0';
	return (0);
}

int	append_space_chevron(t_input *get_input, char *append, size_t start,
		int len_append)
{
	char	*temp;

	temp = ft_calloc(((get_input->len + len_append) + 1), sizeof(char));
	if (!temp)
		return (ft_write(2, "Error malloc"), -1);
	else if (start_append(&temp, start, get_input, append) == -1)
		return (free(temp), -1);
	else if (len_append == 4)
	{
		get_input->len = get_input->len + 4;
		start++;
	}
	else
		get_input->len = get_input->len + 3;
	if (end_append(&temp, start, get_input) == -1)
		return (free(temp), -1);
	free(get_input->input);
	get_input->input = ft_strdup(temp);
	if (!get_input->input)
		return (free(temp), -1);
	free(temp);
	return (0);
}

int	if_operator_no_space(t_input *get_input, char quote, size_t i)
{
	while (get_input->input[i])
	{
		if (get_input->input[i] == '"' || get_input->input[i] == '\'')
		{
			quote = get_input->input[i++];
			while (get_input->input[i] && get_input->input[i] != quote)
				i++;
		}
		if (get_input->input[i] && (get_input->input[i] == '|'
				|| get_input->input[i] == '>' || get_input->input[i] == '<'
				|| get_input->input[i] == '$'))
		{
			if (space_append(get_input, &i) == -1)
				return (-1);
		}
		if (get_input->input[i])
			i++;
	}
	return (0);
}
