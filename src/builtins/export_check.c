/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:55:19 by nkermani          #+#    #+#             */
/*   Updated: 2024/06/27 15:22:15 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"

static bool	ft_isvalidchar(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static bool	ft_check_loop(char *name, bool *in_double_quotes,
		bool *in_single_quotes, bool *eq_sign)
{
	size_t	i;

	i = 1;
	while (name[i])
	{
		if (name[i] == '\'' && !(*in_double_quotes))
			(*in_single_quotes) = !(*in_single_quotes);
		else if (name[i] == '"' && !(*in_single_quotes))
			(*in_double_quotes) = !(*in_double_quotes);
		else if (name[i] == '=' && !(*in_single_quotes) && !(*in_double_quotes))
			(*eq_sign) = true;
		else if (name[i] == '/' && !(*eq_sign) && !(*in_single_quotes)
			&& !(*in_double_quotes))
			return (false);
		else if ((name[i] == ' ' || name[i] == '\t' || name[i] == '\r'
				|| name[i] == '\n' || name[i] == '\v' || name[i] == '\f')
			&& !(*in_single_quotes) && !(*in_double_quotes))
			return (false);
		else if (!(*eq_sign) && !ft_isvalidchar(name[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	ft_check_init(char *name)
{
	if (!name)
		return (false);
	if (!ft_strncmp(name, "if=", 3) || !ft_strncmp(name, "else=", 5)
		|| !ft_strncmp(name, "then=", 5) || !ft_strncmp(name, "fi=", 3)
		|| !ft_strncmp(name, "case=", 5))
		return (false);
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (false);
	return (true);
}

bool	ft_check(char *name)
{
	bool	eq_sign;
	bool	in_single_quotes;
	bool	in_double_quotes;
	size_t	i;

	in_single_quotes = false;
	in_double_quotes = false;
	if (ft_check_init(name) == false)
		return (false);
	eq_sign = false;
	if (ft_check_loop(name, &in_double_quotes, &in_single_quotes,
			&eq_sign) == false)
		return (false);
	if (!eq_sign)
	{
		i = 1;
		while (name[i])
		{
			if (!ft_isvalidchar(name[i]))
				return (false);
			i++;
		}
	}
	return (true);
}
