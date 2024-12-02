/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_here.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:41:40 by afavier           #+#    #+#             */
/*   Updated: 2024/06/24 16:42:36 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static void	count_quote(char **input_quote, char quote, int *j);
static int	end_app_quote(char **tab_split, int j, char **input_quote,
				char *line_temp);
static int	join_end_quote(char **new_line, char **tab_split, int j);

int	remove_quote_char(char **input_quote, char quote)
{
	char	**tab_split;
	char	*line_temp;
	int		result;
	int		j;

	j = 0;
	count_quote(input_quote, quote, &j);
	if (j == 2)
		return (2);
	line_temp = ft_calloc(j + 1, sizeof(char));
	if (!line_temp)
		return (-1);
	ft_strcpy(line_temp, *input_quote, j);
	tab_split = ft_split(line_temp, quote);
	if (!tab_split)
		return (free(line_temp), -1);
	free(line_temp);
	line_temp = ft_strdup((*input_quote + j));
	if (!line_temp)
		return (exec_ft_free_tab(tab_split), -1);
	result = end_app_quote(tab_split, 0, input_quote, line_temp);
	free(line_temp);
	exec_ft_free_tab(tab_split);
	return (result);
}

static void	count_quote(char **input_quote, char quote, int *j)
{
	int	quote_nb;
	int	quote_real;

	quote_nb = 0;
	quote_real = 0;
	while (quote_nb != 2 && (*input_quote)[(*j)] != '\0')
	{
		if ((*input_quote)[(*j)] == quote)
		{
			if ((*input_quote)[(*j) + 1] != '\0' && (*input_quote)[(*j)
				+ 1] == quote && quote_real == 0)
			{
				while ((*input_quote)[(*j)] == quote)
				{
					quote_real++;
					(*j)++;
				}
				(*j)--;
			}
			quote_nb++;
		}
		(*j)++;
	}
}

static int	end_app_quote(char **tab_split, int j, char **input_quote,
		char *line_temp)
{
	char	*new_line;
	int		result;
	char	*temp;

	temp = NULL;
	new_line = NULL;
	while (tab_split[j] != NULL)
	{
		if (join_end_quote(&new_line, tab_split, j) == -1)
			return (free(new_line), -1);
		j++;
	}
	result = ft_strlen(new_line);
	if (new_line)
	{
		(temp) = ft_strjoin(new_line, line_temp);
		if (!(temp))
			return (free(new_line), -1);
		free(*input_quote);
		*input_quote = ft_strdup(temp);
		free(temp);
		if (!*input_quote)
			return (free(new_line), -1);
	}
	return (free(new_line), result);
}

static int	join_end_quote(char **new_line, char **tab_split, int j)
{
	char	*append;

	if (!(*new_line))
	{
		(*new_line) = ft_strdup(tab_split[j]);
		if (!(*new_line))
			return (-1);
	}
	else
	{
		append = ft_strjoin(*new_line, tab_split[j]);
		if (!append)
			return (-1);
		free((*new_line));
		(*new_line) = ft_strdup(append);
		if (!(*new_line))
		{
			free(append);
			return (-1);
		}
		free(append);
	}
	return (0);
}
