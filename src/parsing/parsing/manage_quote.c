/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:36:26 by afavier           #+#    #+#             */
/*   Updated: 2024/06/27 10:59:37 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include <readline/history.h>
#include <readline/readline.h>

static void	count_quote(t_cmd *temp, char quote, int *j);
static int	end_app_quote(char **tab_split, t_cmd *temp, char *line_temp,
				int j);
static int	join_end_quote(char **new_line, char **tab_split, int *j);
static int	split_remove_quote(t_cmd *temp, char quote, int i);

int	remove_quote(t_cmd **cmd)
{
	t_cmd	*temp;
	int		i;

	temp = *cmd;
	while (temp != NULL)
	{
		i = 0;
		while (temp->name[i] != '\0')
		{
			if (temp->name[i] == '"' || temp->name[i] == '\'')
			{
				if (temp->name[i] == '"')
					i = split_remove_quote(temp, '"', i);
				else if (temp->name[i] == '\'')
					i = split_remove_quote(temp, '\'', i);
				if (i == -1)
					return (-1);
				temp->quote = true;
			}
			else
				i++;
		}
		temp = temp->next;
	}
	return (0);
}

static int	split_remove_quote(t_cmd *temp, char quote, int i)
{
	char	**tab_split;
	char	*line_temp;
	int		result;
	int		j;

	j = i;
	count_quote(temp, quote, &j);
	line_temp = ft_calloc(j + 1, sizeof(char));
	if (!line_temp)
		return (-1);
	ft_strcpy(line_temp, temp->name, j);
	tab_split = ft_split(line_temp, quote);
	if (!tab_split)
		return (free(line_temp), -1);
	free(line_temp);
	line_temp = ft_strdup(&(temp->name[j]));
	if (!line_temp)
		return (exec_ft_free_tab(tab_split), -1);
	result = end_app_quote(tab_split, temp, line_temp, 0);
	return (exec_ft_free_tab(tab_split), free(line_temp), result);
}

static void	count_quote(t_cmd *temp, char quote, int *j)
{
	int	quote_nb;

	quote_nb = 1;
	(*j)++;
	while ((quote_nb % 2 != 0) && temp->name[(*j)] != '\0')
	{
		if (temp->name[(*j)] != quote && (temp->name[(*j)] == '"'
				|| temp->name[(*j)] == '\''))
			temp->name[(*j)] = temp->name[(*j)] * (-1);
		while (temp->name[(*j)] == quote)
		{
			quote_nb++;
			(*j)++;
			if (quote_nb % 2 != 0 && (temp->name[(*j)] == ' '))
				temp->name[(*j)] = temp->name[(*j)] * (-1);
			if (temp->name[(*j)] != quote)
			{
				(*j)--;
				break ;
			}
		}
		(*j)++;
	}
}

static int	end_app_quote(char **tab_split, t_cmd *temp, char *line_temp, int j)
{
	char	*new_line;

	new_line = NULL;
	while (tab_split[j])
	{
		if (join_end_quote(&new_line, tab_split, &j) == -1)
			return (-1);
		j++;
	}
	if (new_line)
	{
		free(temp->name);
		temp->name = ft_strjoin(new_line, line_temp);
		if (!temp->name)
			return (free(new_line), -1);
	}
	else
	{
		free(temp->name);
		temp->name = ft_strdup(line_temp);
		if (!temp->name)
			return (free(new_line), -1);
	}
	return (free(new_line), 0);
}

static int	join_end_quote(char **new_line, char **tab_split, int *j)
{
	char	*append;

	if (!(*new_line))
	{
		(*new_line) = ft_strdup(tab_split[*j]);
		if (!(*new_line))
			return (-1);
	}
	else
	{
		append = ft_strjoin((*new_line), tab_split[*j]);
		if (!append)
			return (-1);
		free((*new_line));
		(*new_line) = ft_strdup(append);
		if (!(*new_line))
			return (free(append), -1);
		free(append);
	}
	return (0);
}
