/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 20:06:53 by nkermani          #+#    #+#             */
/*   Updated: 2024/03/04 17:44:01 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			words++;
			while (s[i] && (s[i] != c))
				i++;
		}
		else if (s[i])
			i++;
	}
	return (words);
}

static size_t	word_len(size_t i, char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static void	*total_free(char **str2d)
{
	size_t	i;

	i = 0;
	while (str2d[i])
		free(str2d[i++]);
	free(str2d);
	return (NULL);
}

static char	**fill_words(char **str2d, size_t words, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i] && j < words)
	{
		while (s[i] == c)
			i++;
		str2d[j] = (char *)malloc(sizeof(char) * (word_len(i, s, c) + 1));
		if (!str2d[j])
			return (total_free(str2d));
		k = 0;
		while (s[i] && s[i] != c)
		{
			str2d[j][k] = s[i];
			i++;
			k++;
		}
		str2d[j][k] = 0;
		j++;
	}
	str2d[j] = 0;
	return (str2d);
}

char	**ft_split(char const *s, char c)
{
	char	**str2d;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	str2d = (char **)malloc(sizeof(char *) * (words + 1));
	if (!str2d)
		return (NULL);
	return (fill_words(str2d, words, s, c));
}
