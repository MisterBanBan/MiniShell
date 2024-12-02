/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_dollars_here.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:41:35 by afavier           #+#    #+#             */
/*   Updated: 2024/06/11 13:26:34 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	remove_dollars(char **input_dollars, size_t start)
{
	char	*new_line;
	char	*append;

	new_line = ft_calloc(ft_strlen(*input_dollars), sizeof(char));
	if (!new_line)
		return (-1);
	ft_strcpy(new_line, (*input_dollars), start);
	append = ft_strjoin(new_line, (*input_dollars + start + 1));
	if (!append)
	{
		free(new_line);
		return (-1);
	}
	if (new_line)
	{
		free(*input_dollars);
		(*input_dollars) = ft_strdup(append);
		free(new_line);
		free(append);
	}
	return (0);
}
