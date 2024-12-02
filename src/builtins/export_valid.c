/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:58:33 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/23 01:55:43 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"

static int	ft_is_valid_identifier(const char *str)
{
	if (!str || !*str || ft_isdigit(*str) || *str == '=')
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

static void	equal_pos_not_null(char **key, char **equal_pos, char **value,
		char *token)
{
	*key = token;
	**equal_pos = '\0';
	*value = *equal_pos + 1;
	while (**key == ' ')
		(*key)++;
	while (*(*equal_pos - 1) == ' ')
		(*equal_pos)--;
	**equal_pos = '\0';
	while (**value == ' ')
		(*value)++;
	if (!ft_is_valid_identifier(*key) || ft_strchr(*key, ' '))
	{
		ft_whitespace_back_to_pos(&(*key));
		ft_write(2, "Quectoshell: not a valid identifier\n");
	}
}

void	validate_export_string(char *str)
{
	char		*token;
	const char	*delim = " ";
	char		*equal_pos;
	char		*key;
	char		*value;

	if (ft_strncmp(str, "export", 6) == 0)
		str += 7;
	token = ft_strtok(str, delim);
	while (token != NULL)
	{
		str = NULL;
		equal_pos = ft_strchr(token, '=');
		if (equal_pos != NULL)
			equal_pos_not_null(&key, &equal_pos, &value, token);
		else
		{
			if (!ft_is_valid_identifier(token) || ft_strchr(token, ' '))
			{
				ft_whitespace_back_to_pos(&token);
				ft_write(2, "Quectoshell: not a valid identifier\n");
			}
		}
		token = ft_strtok(str, delim);
	}
}
