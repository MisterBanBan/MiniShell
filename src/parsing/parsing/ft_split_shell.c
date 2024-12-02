/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:28:03 by afavier           #+#    #+#             */
/*   Updated: 2024/07/09 03:17:14 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	quote_search(char const *s, size_t i);
static size_t	word_len_shell(size_t i, char const *s);
static char		**fill_words_shell(char **str2d, ssize_t words, char const *s,
					ssize_t i);

static size_t	count_words_shell(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] && (s[i] != c && s[i] != '\t' && s[i] != '\r' && s[i] != '\n'
				&& s[i] != '\v' && s[i] != '\f'))
		{
			words++;
			while (s[i] && (s[i] != c && s[i] != '\t' && s[i] != '\r'
					&& s[i] != '\n' && s[i] != '\v' && s[i] != '\f'))
			{
				if (s[i] == '\'' || s[i] == '"')
					i = quote_search(s, i) - 1;
				i++;
			}
		}
		while (s[i] && (s[i] == c || s[i] == '\t' || s[i] == '\r'
				|| s[i] == '\n' || s[i] == '\v' || s[i] == '\f'))
			i++;
	}
	i--;
	return (words);
}

static size_t	quote_search(char const *s, size_t i)
{
	size_t	one_quote;
	size_t	double_quote;

	one_quote = 0;
	double_quote = 0;
	if (s[i] == '\'')
		one_quote = 1;
	if (s[i] == '"')
		double_quote = 1;
	i++;
	while (s[i] && ((one_quote != 0 && one_quote % 2 != 0) || (double_quote != 0
				&& double_quote % 2 != 0)))
	{
		if (s[i] == '\'' && one_quote != 0)
			one_quote++;
		if (s[i] == '"' && double_quote != 0)
			double_quote++;
		i++;
	}
	return (i);
}

static size_t	word_len_shell(size_t i, char const *s)
{
	size_t	len;
	size_t	len_i;

	len = 0;
	len_i = i;
	while (s[i] && (s[i] != ' ' && s[i] != '\t' && s[i] != '\r' && s[i] != '\n'
			&& s[i] != '\v' && s[i] != '\f'))
	{
		if (s[i] == '"' || s[i] == '\'')
			i = quote_search(s, i);
		else
			i++;
	}
	len = i - len_i;
	return (len);
}

static char	**fill_words_shell(char **str2d, ssize_t words, char const *s,
		ssize_t i)
{
	ssize_t	ind[3];

	ind[0] = -1;
	while (s[i] && ++(ind[0]) <= words)
	{
		ind[1] = skip_white_spaces(s, &i);
		str2d[ind[0]] = ft_calloc((word_len_shell(i, s) + 1), sizeof(char));
		if (!str2d[ind[0]])
			return (total_free_shell(str2d));
		while (s[i] && (s[i] != ' ' && s[i] != '\t' && s[i] != '\r'
				&& s[i] != '\n' && s[i] != '\v' && s[i] != '\f'))
		{
			if (s[i] == '"' || s[i] == '\'')
			{
				ind[2] = quote_search(s, i);
				while (i < ind[2])
					str2d[ind[0]][(ind[1])++] = s[i++];
			}
			else
				str2d[ind[0]][(ind[1])++] = s[i++];
		}
	}
	if (++(ind[0]) < words)
		return (total_free_shell(str2d));
	return (str2d);
}

char	**ft_split_shell(char const *s, char c)
{
	char	**str2d;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words_shell(s, c);
	str2d = ft_calloc(words + 2, sizeof(char *));
	if (!str2d)
		return (NULL);
	return (fill_words_shell(str2d, words, s, 0));
}
