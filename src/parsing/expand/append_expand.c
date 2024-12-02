/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:39:51 by afavier           #+#    #+#             */
/*   Updated: 2024/07/18 23:26:32 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"

static int	append_start_expand(char **first, char *append, size_t start,
				char *input);
static int	append_end_expand(char **first, char *input, size_t end);
static int	free_append(char **first, char **temp);

char	*append_expand(char *input, char *append, size_t start, size_t end)
{
	char	*first;

	if (append == NULL)
		first = ft_calloc((ft_strlen(input) - (end - (start + 1))),
				sizeof(char));
	else
		first = ft_calloc(((ft_strlen(input) - (end - (start + 1)))
					+ ft_strlen(append)) + 1, sizeof(char));
	if (!first)
		return (ft_write(2, "Error malloc"), NULL);
	if (append_start_expand(&first, append, start - 1, input) == -1)
	{
		free(first);
		return (NULL);
	}
	if (append_end_expand(&first, input, end) == -1)
	{
		free(first);
		return (NULL);
	}
	return (first);
}

static int	append_start_expand(char **first, char *append, size_t start,
		char *input)
{
	char	*temp;

	temp = NULL;
	ft_strcpy((*first), input, start);
	if (append != NULL)
	{
		if (start + 1 > 1)
		{
			temp = ft_strjoin((*first), append);
			if (!temp)
				return (-1);
		}
		else
		{
			temp = ft_strdup(append);
			if (!temp)
				return (ft_write(2, "malloc failed\n"), -1);
		}
		if (free_append(first, &temp) == -1)
			return (free(temp), -1);
	}
	free(temp);
	return (0);
}

static int	free_append(char **first, char **temp)
{
	free(*first);
	(*first) = ft_strdup(*temp);
	if (!*first)
		return (ft_write(2, "Error mallocc"), -1);
	return (0);
}

static int	append_end_expand(char **first, char *input, size_t end)
{
	char	*temp;

	temp = ft_strjoin((*first), &(input[end]));
	if (!temp)
		return (-1);
	free(*first);
	*first = ft_strdup(temp);
	if (!*first)
		return (free(temp), ft_write(2, "Error malloccc"), -1);
	free(temp);
	return (0);
}
