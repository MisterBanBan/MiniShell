/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:20:42 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 23:20:38 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"

static int	ft_env_elem_change(char ****envp, int i)
{
	char	*tmp;
	char	*tmp2;

	if (i != ((int)exec_ft_tab_len((*envp)[0]) - 1))
	{
		tmp = ft_strdup((*envp)[0][exec_ft_tab_len((*envp)[0]) - 1]);
		if (!tmp)
			return (ft_write(2, "malloc failed\n"), -1);
		tmp2 = ft_strdup((*envp)[0][exec_ft_tab_len((*envp)[1]) - 1]);
		if (!tmp2)
			return (free(tmp), ft_write(2, "malloc failed\n"), -1);
		free((*envp)[0][i]);
		free((*envp)[1][i]);
		(*envp)[0][i] = tmp;
		(*envp)[1][i] = tmp2;
		free((*envp)[0][exec_ft_tab_len((*envp)[0]) - 1]);
		free((*envp)[1][exec_ft_tab_len((*envp)[1]) - 1]);
		(*envp)[0][exec_ft_tab_len((*envp)[0]) - 1] = NULL;
		(*envp)[1][exec_ft_tab_len((*envp)[1]) - 1] = NULL;
	}
	return (0);
}

static void	ft_env_elem_last(char ****envp, int i)
{
	free((*envp)[0][i]);
	free((*envp)[1][i]);
	(*envp)[0][i] = NULL;
	(*envp)[1][i] = NULL;
}

int	ft_unset_single(char *name, char ***envp)
{
	int		i;
	char	**name_val;

	name_val = ft_get_name_val(name);
	i = 0;
	while (envp[0] && envp[0][i])
	{
		if (!ft_strcmp(name_val[0], envp[0][i]))
		{
			if (i != ((int)exec_ft_tab_len(envp[0]) - 1))
			{
				if (ft_env_elem_change(&envp, i) == -1)
					return (-1);
			}
			else
				ft_env_elem_last(&envp, i);
		}
		i++;
	}
	free(name_val[0]);
	free(name_val[1]);
	free(name_val);
	return (0);
}

int	ft_unset(char *name, t_exe_builtin **new_env)
{
	char	**names;
	int		result;
	int		i;

	result = 0;
	if (!name || !(*new_env)->envp_b)
		return (0);
	names = ft_split_shell(name, ' ');
	if (!names)
		return (free(name), ft_write(2, "malloc failed"), 1);
	i = 0;
	while (names[i])
	{
		if (ft_unset_single(names[i], (*new_env)->name_val) == -1)
			result = 1;
		ft_update_env(new_env);
		free(names[i]);
		i++;
	}
	free(names);
	free(name);
	return (result);
}
