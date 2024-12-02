/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:40:00 by afavier           #+#    #+#             */
/*   Updated: 2024/07/18 23:25:51 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>

static int	wrong_quote_or_not(int s_quote, int d_quote);
static void	nb_quote(int *d_quote, int *s_quote, t_input *get_input, size_t i);

int	check_quote(t_input *get_input)
{
	size_t	i;
	int		d_quote;
	int		s_quote;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (get_input->input[i] != '\0')
	{
		nb_quote(&d_quote, &s_quote, get_input, i);
		i++;
		if (d_quote == 2 || s_quote == 2)
		{
			d_quote = 0;
			s_quote = 0;
		}
	}
	if (wrong_quote_or_not(s_quote, d_quote) == -1)
		return (-1);
	return (0);
}

static int	wrong_quote_or_not(int s_quote, int d_quote)
{
	if (s_quote % 2 != 0 || d_quote % 2 != 0)
	{
		ft_write(2, "Wrong quote\n");
		return (-1);
	}
	return (0);
}

static void	nb_quote(int *d_quote, int *s_quote, t_input *get_input, size_t i)
{
	if ((*s_quote) == 0 && (*d_quote) == 0)
	{
		if (get_input->input[i] == '\'')
			(*s_quote)++;
		if (get_input->input[i] == '"')
			(*d_quote)++;
	}
	else if ((*s_quote) > 0 && get_input->input[i] == '\'')
		(*s_quote)++;
	else if ((*d_quote) > 0 && get_input->input[i] == '"')
		(*d_quote)++;
}
