/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:33:39 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 23:20:52 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"

static int	exec_ft_init_no_env(t_exe_builtin **new_env,
		t_exe_builtin **exe_envp)
{
	(*exe_envp)->envp_b = NULL;
	(*exe_envp)->name_val = (char ***)malloc(sizeof(char **) * 2);
	if (!(*exe_envp)->name_val)
		return (ft_write(2, "malloc failed"), -1);
	(*exe_envp)->name_val[0] = (char **)malloc(sizeof(char *) * 2);
	(*exe_envp)->name_val[1] = (char **)malloc(sizeof(char *) * 2);
	(*new_env) = (*exe_envp);
	return (0);
}

static int	exec_ft_init_with_env(t_exe_builtin **exe_envp, char **envp)
{
	(*exe_envp)->envp_b = exec_ft_tab_dup(envp);
	if (!((*exe_envp)->envp_b))
		return (free((*exe_envp)), -1);
	(*exe_envp)->name_val = (char ***)malloc(sizeof(char **) * 2);
	if (!(*exe_envp)->name_val)
		return (ft_write(2, "malloc failed\n"),
			exec_ft_free_tab((*exe_envp)->envp_b), free((*exe_envp)), -1);
	(*exe_envp)->name_val[0] = exec_ft_tab_dup_names(envp);
	if (!((*exe_envp)->name_val[0]))
		return (free((*exe_envp)->name_val),
			exec_ft_free_tab((*exe_envp)->envp_b), free((*exe_envp)), -1);
	(*exe_envp)->name_val[1] = exec_ft_tab_dup_values(envp);
	if (!((*exe_envp)->name_val[1]))
		return (exec_ft_free_tab((*exe_envp)->name_val[0]),
			free((*exe_envp)->name_val), exec_ft_free_tab((*exe_envp)->envp_b),
			free((*exe_envp)), -1);
	return (0);
}

int	exec_ft_init_exe_envp(t_exe_builtin **new_env, char **envp)
{
	t_exe_builtin	*exe_envp;

	exe_envp = (t_exe_builtin *)malloc(sizeof(t_exe_builtin));
	if (!exe_envp)
		return (-1);
	exe_envp->cwd = NULL;
	exe_envp->oldpwd = NULL;
	exe_envp->res = 0;
	if (!envp || *envp == NULL)
	{
		if (exec_ft_init_no_env(new_env, &exe_envp) == -1)
			return (-1);
	}
	else
	{
		if (exec_ft_init_with_env(&exe_envp, envp) == -1)
			return (-1);
	}
	(*new_env) = exe_envp;
	return (0);
}
