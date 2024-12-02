/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:58:31 by afavier           #+#    #+#             */
/*   Updated: 2024/07/17 00:54:49 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"
#include "parsing.h"

static void		nb_quote_pars(char *input, int *quote_d, int *quote_s, int i);
static size_t	no_expand_heredoc(char *inp, size_t i, char here_doc);
static char		*start_expand_var(char **input, size_t *i, char ***env);
static int		copy_input(char **temp, size_t *i, char ***env, char quote_s);

char	*expand_var(char *input, char ***env)
{
	size_t	i;
	int		quote_d;
	int		quote_s;
	char	*temp;

	i = 0;
	quote_d = 0;
	quote_s = 0;
	temp = ft_strdup(input);
	if (!temp)
		return (NULL);
	while (temp[i] != '\0')
	{
		nb_quote_pars(temp, &quote_d, &quote_s, i);
		i = no_expand_heredoc(temp, i, 0);
		if (temp[i] != '\0')
		{
			if (copy_input(&temp, &i, env, quote_s) == -1)
			{
				free(temp);
				return (NULL);
			}
		}
	}
	return (temp);
}

static int	copy_input(char **temp, size_t *i, char ***env, char quote_s)
{
	if ((*temp)[(*i)] != '\0' && (*temp)[(*i)] == '$' && ((quote_s % 2) == 0)
		&& (*temp)[(*i) + 1] != '\0' && (((*temp)[(*i) + 1] >= 'a'
				&& (*temp)[(*i) + 1] <= 'z') || ((*temp)[(*i) + 1] >= 'A'
				&& (*temp)[(*i) + 1] <= 'Z') || ((*temp)[(*i) + 1] == '_')
			|| ((*temp)[(*i) + 1] >= '1' && (*temp)[(*i) + 1] <= '9')))
	{
		if ((*temp)[(*i) + 1] == '?' && ((*temp)[(*i) + 2] == '\0'
				|| (*temp)[(*i) + 2] != '\t' || (*temp)[(*i) + 2] != '\r'
				|| (*temp)[(*i) + 2] != '\n' || (*temp)[(*i) + 2] != '\v'
				|| (*temp)[(*i) + 2] != '\f'))
		{
			*i = *i + 2;
			return (0);
		}
		*temp = start_expand_var(temp, i, env);
		if (!*temp)
			return (-1);
	}
	else if ((*temp)[(*i)] != '\0')
		(*i)++;
	return (0);
}

static char	*start_expand_var(char **in, size_t *i, char ***env)
{
	size_t	start_expand;
	size_t	size;
	char	*string_env;
	char	*append;
	char	*expand_input;

	start_expand = ++(*i);
	expand_num(in, i);
	size = (*i) - start_expand;
	string_env = ft_substr(*in, start_expand, size);
	if (!string_env)
		return (free(*in), NULL);
	append = ft_strdup(find_path(env, string_env));
	free(string_env);
	if (append)
		path(append);
	expand_input = append_expand(*in, append, start_expand, (*i));
	if (!expand_input)
		return (free(append), free(*in), NULL);
	(*i) = start_expand - 1;
	if (append != NULL && append[0] == '$')
		(*i)++;
	return (free(*in), free(append), expand_input);
}

static void	nb_quote_pars(char *input, int *quote_d, int *quote_s, int i)
{
	if (input[i] == '"')
		(*quote_d)++;
	if (input[i] == '\'')
	{
		if ((*quote_d) % 2 != 0)
			(*quote_s) = 0;
		else
			(*quote_s)++;
	}
}

static size_t	no_expand_heredoc(char *inp, size_t i, char here_doc)
{
	if (inp[i + 1] != '\0' && inp[i] == '<' && inp[i + 1] == '<')
	{
		i += 2;
		while (inp[i] != '\0' && (inp[i] == ' ' || inp[i] == '\t'
				|| inp[i] == '\r' || inp[i] == '\n' || inp[i] == '\v'
				|| inp[i] == '\f'))
			i++;
		while (inp[i] != '\0' && (inp[i] != ' ' && inp[i] != '\t'
				&& inp[i] != '\r' && inp[i] != '\n' && inp[i] != '\v'
				&& inp[i] != '\f'))
		{
			if (inp[i] == '\'' || inp[i] == '"')
			{
				here_doc = inp[i];
				i++;
				while (inp[i] != '\0' && here_doc != inp[i])
					i++;
				if (inp[i] == here_doc)
					i++;
			}
			else
				i++;
		}
	}
	return (i);
}
