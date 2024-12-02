/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:20:36 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/17 01:15:03 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"

static int	ft_export_loop(char ***names, char *name, t_exe_builtin **new_env)
{
	int	i;

	i = 0;
	(*names) = ft_split_shell(name, ' ');
	if (!(*names))
		return (1);
	while ((*names)[(i)])
	{
		if (ft_check((*names)[(i)]))
		{
			if (ft_export_append((*names)[(i)], new_env) == -1)
			{
				perror("append failed");
				exec_ft_free_tab((*names));
				return (1);
			}
		}
		(i) += 1;
	}
	exec_ft_free_tab((*names));
	validate_export_string(name);
	return (0);
}

static int	white_space(char *line)
{
	int	i;

	i = 0;
	while (line && (line[i]))
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\r'
			&& line[i] != '\n' && line[i] != '\v' && line[i] != '\f')
			return (0);
		i++;
	}
	return (-1);
}

int	ft_export(char *name, t_exe_builtin **new_env)
{
	char	**names;

	names = NULL;
	if (white_space(name) == -1)
	{
		free(name);
		name = NULL;
	}
	if (!name)
	{
		if ((*new_env) && (*new_env)->name_val)
			ft_export_no_args((*new_env)->name_val);
		return (0);
	}
	else
	{
		if (ft_export_loop(&names, name, new_env) == -1)
			return (free(name), -1);
	}
	return (free(name), 0);
}
