/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:51:01 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 23:18:41 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "struct.h"
#include "utils.h"
#include <linux/limits.h>

char	*get_env_value(char **envp, const char *var)
{
	size_t	len;
	int		i;
	char	*env_val;

	len = ft_strlen(var);
	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
		{
			env_val = ft_strdup(envp[i] + len + 1);
			if (!env_val)
				return (ft_write(2, "malloc failed\n"), NULL);
			return (env_val);
		}
		i++;
	}
	return (NULL);
}

int	change_directory(t_exe_builtin *exe_env, char *curpath)
{
	char	*oldpwd;
	char	*pwd;

	if (chdir(curpath) != 0)
		return (ft_putstr_fd("cd: ", 2), ft_putstr_fd(strerror(errno), 2),
			ft_putstr_fd("\n", 2), 1);
	if (exe_env)
	{
		free(exe_env->oldpwd);
		exe_env->oldpwd = ft_strdup(exe_env->cwd);
		free(exe_env->cwd);
		exe_env->cwd = getcwd(NULL, 0);
		if (!exe_env->cwd)
			ft_write(2, "getcwd failed\n");
		oldpwd = ft_strjoin("OLDPWD=", exe_env->oldpwd);
		pwd = ft_strjoin("PWD=", exe_env->cwd);
		if (!exe_env->oldpwd || !oldpwd | !pwd)
			ft_write(2, "malloc failed\n");
		ft_export(oldpwd, &(exe_env));
		ft_export(pwd, &(exe_env));
	}
	return (0);
}

int	ft_cd_too_long(char **home, char **canonical)
{
	if (ft_strlen(*canonical) > PATH_MAX)
	{
		ft_putstr_fd("cd: path too long\n", 2);
		free(*canonical);
		free(*home);
		return (1);
	}
	return (0);
}
