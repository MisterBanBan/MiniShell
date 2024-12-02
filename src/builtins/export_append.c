/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:02:24 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 23:19:22 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

int	ft_update_env(t_exe_builtin **new_env)
{
	int		i;
	char	*str1;
	char	*str2;

	i = 0;
	exec_ft_free_tab((*new_env)->envp_b);
	(*new_env)->envp_b = (char **)malloc(sizeof(char *)
			* ((int)exec_ft_tab_len((*new_env)->name_val[0]) + 1));
	if (!(*new_env)->envp_b)
		return (ft_write(2, "malloc failed\n"), -1);
	while ((*new_env)->name_val && (*new_env)->name_val[0][i])
	{
		if ((*new_env)->name_val[1][i])
		{
			str1 = ft_strjoin((*new_env)->name_val[0][i], "=");
			str2 = ft_strjoin(str1, (*new_env)->name_val[1][i]);
			free(str1);
			(*new_env)->envp_b[i] = str2;
		}
		else
			(*new_env)->envp_b[i] = ft_strdup((*new_env)->name_val[0][i]);
		i++;
	}
	(*new_env)->envp_b[i] = NULL;
	return (0);
}

static int	ft_append_fill_name(char ****tmp, char **name_val,
		t_exe_builtin **new_env)
{
	int	i;

	i = 0;
	(*tmp)[0] = (char **)malloc(sizeof(char *)
			* (exec_ft_tab_len((*new_env)->name_val[0]) + 1 + 1));
	if (!(*tmp)[0])
		return (ft_write(2, "malloc failed\n"), -1);
	while ((*new_env)->name_val && (*new_env)->name_val[0][i])
	{
		(*tmp)[0][i] = ft_strdup((*new_env)->name_val[0][i]);
		if (!(*tmp)[0][i])
			return (ft_write(2, "malloc failed\n"), -1);
		i++;
	}
	(*tmp)[0][i] = ft_strdup(name_val[0]);
	if (!(*tmp)[0][i])
		return (ft_write(2, "malloc failed\n"), -1);
	(*tmp)[0][i + 1] = NULL;
	exec_ft_free_tab((*new_env)->name_val[0]);
	(*new_env)->name_val[0] = (*tmp)[0];
	return (0);
}

static int	ft_append_fill_values(char ****tmp, char **name_val,
		t_exe_builtin **new_env)
{
	int	i;

	i = 0;
	(*tmp)[1] = (char **)malloc(sizeof(char *)
			* (exec_ft_tab_len((*new_env)->name_val[0]) + 1 + 1));
	if (!(*tmp)[1])
		return (ft_write(2, "malloc failed\n"), -1);
	while ((*new_env)->name_val && (*new_env)->name_val[0][i]
		&& ft_strcmp(name_val[0], (*new_env)->name_val[0][i]))
	{
		if ((*new_env)->name_val[1][i])
			(*tmp)[1][i] = ft_strdup((*new_env)->name_val[1][i]);
		else
			(*tmp)[1][i] = NULL;
		i++;
	}
	(*tmp)[1][i] = ft_strdup(name_val[1]);
	(*tmp)[1][i + 1] = NULL;
	exec_ft_free_tab((*new_env)->name_val[1]);
	(*new_env)->name_val[1] = (*tmp)[1];
	return (0);
}

int	ft_append(char **name_val, t_exe_builtin **new_env)
{
	char	***tmp;

	tmp = (char ***)malloc(sizeof(char **) * 2);
	if (!tmp)
		return (ft_write(2, "malloc failed\n"), -1);
	if (ft_append_fill_name(&tmp, name_val, new_env) == -1)
		return (free(tmp), ft_write(2, "malloc failed\n"), -1);
	if (ft_append_fill_values(&tmp, name_val, new_env) == -1)
		return (exec_ft_free_tab(tmp[0]), free(tmp), ft_write(2,
				"malloc failed\n"), -1);
	free(tmp);
	return (0);
}

int	ft_export_append(char *name, t_exe_builtin **new_env)
{
	char	**name_val;

	ft_whitespace_back_to_pos(&name);
	name_val = ft_get_name_val(name);
	if (!name_val)
		return (ft_write(2, "malloc failed\n"), -1);
	if (ft_check_in_env(name_val, (*new_env)->name_val))
	{
		ft_replace(name_val, new_env);
	}
	else
	{
		ft_append(name_val, new_env);
	}
	ft_update_env(new_env);
	free(name_val[0]);
	free(name_val[1]);
	free(name_val);
	return (0);
}
