/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:06:42 by afavier           #+#    #+#             */
/*   Updated: 2024/06/15 16:11:47 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	skip_white_spaces(char const *s, ssize_t *i)
{
	while (s[*i] == ' ' || s[*i] == '\t'
		|| s[*i] == '\r' || s[*i] == '\n'
		|| s[*i] == '\v' || s[*i] == '\f')
		(*i)++;
	return (0);
}

void	*total_free_shell(char **str2d)
{
	size_t	i;

	i = 0;
	if (!str2d)
		return (NULL);
	while (str2d[i])
		free(str2d[i++]);
	free(str2d);
	return (NULL);
}
