/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:03:50 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 23:17:58 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

static int	ft_replace_init(char **name_val, t_exe_builtin **new_env, int i)
{
	free((*new_env)->name_val[0][i]);
	(*new_env)->name_val[0][i] = ft_strdup(name_val[0]);
	if (!(*new_env)->name_val[0][i])
		return (ft_write(2, "malloc failed\n"), -1);
	return (0);
}

static int	ft_replace_process(char **name_val, t_exe_builtin **new_env, int i)
{
	if (name_val[1])
	{
		free((*new_env)->name_val[1][i]);
		(*new_env)->name_val[1][i] = ft_strdup(name_val[1]);
		if (!(*new_env)->name_val[1][i])
			return (ft_write(2, "malloc failed\n"), -1);
	}
	else
	{
		if ((*new_env)->name_val[1][i])
		{
			free((*new_env)->name_val[1][i]);
			(*new_env)->name_val[1][i] = NULL;
		}
		else
			(*new_env)->name_val[1][i] = NULL;
	}
	return (0);
}

int	ft_replace(char **name_val, t_exe_builtin **new_env)
{
	int	i;

	i = 0;
	while ((*new_env)->name_val[0] && (*new_env)->name_val[0][i])
	{
		if (!ft_strcmp(name_val[0], (*new_env)->name_val[0][i]))
		{
			if (ft_replace_init(name_val, new_env, i) == -1)
				return (-1);
			if (ft_replace_process(name_val, new_env, i) == -1)
				return (-1);
			return (0);
		}
		i++;
	}
	return (1);
}
