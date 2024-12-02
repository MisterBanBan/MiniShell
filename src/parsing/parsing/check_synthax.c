/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_synthax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:40:08 by afavier           #+#    #+#             */
/*   Updated: 2024/07/17 01:12:28 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>

static void	inc_len(t_input *get_input, size_t *start, size_t *len);
static void	start_check(t_input *get_input, size_t *start, size_t *i);
static int	check_pipe(t_input *get_inp, int i, int len);

int	check_synthax(t_input *get_input, size_t len, size_t i)
{
	size_t	start;

	while (get_input && get_input->input[i])
	{
		if (get_input->input[i] == '"' || get_input->input[i] == '\'')
			check_quote_synthax(get_input, &i);
		if (check_pipe(get_input, i, 0) == -1)
			return (-1);
		if (check_pipe_after(get_input, i, 0) == -1)
			return (-1);
		if ((get_input->input[i] == '<' && get_input->input[i + 1] == '<')
			|| (get_input->input[i] == '>' && get_input->input[i + 1] == '>')
			|| get_input->input[i] == '>' || get_input->input[i] == '<')
		{
			start_check(get_input, &start, &i);
			inc_len(get_input, &start, &len);
			if (len == 0 && (i + 1 > get_input->len || get_input->input[i
						+ 1] != '|'))
				return (-1);
			len = 0;
		}
		if (get_input->input[i])
			i++;
	}
	return (0);
}

static int	check_pipe(t_input *get_inp, int i, int len)
{
	if (get_inp->input[i] == '|')
	{
		i--;
		while (i >= 0)
		{
			if (get_inp->input[i] == '|' || (i - 1 >= 0
					&& get_inp->input[i] == '<' && get_inp->input[i - 1] == '<')
				|| (i - 1 >= 0 && get_inp->input[i] == '>' && get_inp->input[i
						- 1] == '>') || (get_inp->input[i] == '<')
				|| (get_inp->input[i] == '>'))
				break ;
			if (get_inp->input[i] == '_' || (get_inp->input[i] >= 'a'
					&& get_inp->input[i] <= 'z') || (get_inp->input[i] >= 'A'
					&& get_inp->input[i] <= 'Z') || (get_inp->input[i] == '"')
				|| (get_inp->input[i] >= '1' && get_inp->input[i] <= '9')
				|| (get_inp->input[i] == '\''))
				len++;
			i--;
		}
		if (len == 0)
			return (-1);
	}
	return (0);
}

static void	inc_len(t_input *get_input, size_t *start, size_t *len)
{
	while (get_input->input[(*start)])
	{
		if (get_input->input[(*start)] == '_'
			|| (get_input->input[(*start)] >= 'a'
				&& get_input->input[(*start)] <= 'z')
			|| (get_input->input[(*start)] >= 'A'
				&& get_input->input[(*start)] <= 'Z')
			|| (get_input->input[(*start)] >= '1'
				&& get_input->input[(*start)] <= '9'))
			(*len)++;
		if (get_input->input[(*start)] == '|'
			|| (get_input->input[(*start)] == '<' && get_input->input[(*start)
					+ 1] == '<') || (get_input->input[(*start)] == '>'
				&& get_input->input[(*start) + 1] == '>')
			|| get_input->input[(*start)] == '>'
			|| get_input->input[(*start)] == '<')
			break ;
		(*start)++;
	}
}

static void	start_check(t_input *get_input, size_t *start, size_t *i)
{
	if ((get_input->input[(*i)] == '<' && get_input->input[(*i) + 1] == '<')
		|| (get_input->input[(*i)] == '>' && get_input->input[(*i) + 1] == '>'))
	{
		(*i) = (*i) + 2;
		(*start) = (*i);
	}
	else
		(*start) = (*i) + 1;
}

int	if_pipe_space(t_input *get_input, size_t *i)
{
	if (get_input->input[*i] == '|')
	{
		if (append_space_chevron(get_input, " | ", *i, 3) == -1)
			return (-1);
	}
	return (0);
}
