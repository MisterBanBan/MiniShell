/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:40:36 by afavier           #+#    #+#             */
/*   Updated: 2024/07/18 05:33:54 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"
#include "parsing.h"

char	*find_path(char ***env, char *path)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[0][i])
	{
		if (!ft_strncmp(path, env[0][i], ft_strlen(path) + 1))
			return (env[1][i]);
		i++;
	}
	return (NULL);
}

void	path(char *append)
{
	int	i;

	i = 0;
	while (append[i])
	{
		if (append[i] == '\'' || append[i] == '"' || append[i] == '>'
			|| append[i] == '<' || append[i] == '|')
			append[i] = append[i] * (-1);
		i++;
	}
}

void	expand_num(char **in, size_t *i)
{
	if ((*in)[(*i)] != '\0' && ((*in)[(*i)] >= '0' && (*in)[(*i)] <= '9'))
		(*i)++;
	else
	{
		while (((*in)[(*i)] >= 'a' && (*in)[(*i)] <= 'z') || ((*in)[(*i)] >= 'A'
				&& (*in)[(*i)] <= 'Z') || ((*in)[(*i)] == '_')
			|| ((*in)[(*i)] >= '1' && (*in)[(*i)] <= '9'))
			(*i)++;
	}
}
