/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:20:18 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 23:18:54 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "struct.h"
#include "utils.h"
#include <linux/limits.h>

static int	ft_cd_init(t_exe_builtin **exe_env, char **home)
{
	if (!(*exe_env))
	{
		ft_write(2, "exe_env == NULL\n");
		return (-1);
	}
	if (!(*exe_env)->cwd)
	{
		(*exe_env)->cwd = getcwd(NULL, 0);
		if (!(*exe_env)->cwd)
		{
			ft_write(2, "getcwd failed\n");
			return (-1);
		}
	}
	*home = get_env_value((*exe_env)->envp_b, "HOME");
	return (0);
}

static int	ft_before_change_dir(char **canonical, char **curpath, char **home)
{
	(*canonical) = canonicalize_path(*curpath);
	free((*curpath));
	if (!(*canonical))
	{
		free(*home);
		return (-1);
	}
	if (ft_cd_too_long(home, canonical) == -1)
		return (-1);
	return (0);
}

int	ft_cd(char *new_dir, t_exe_builtin **exe_env)
{
	char	*curpath;
	char	*home;
	char	*canonical;
	int		res;

	res = 0;
	if (ft_cd_init(exe_env, &home) == -1)
	{
		ft_write(2, "cd init has failed\n");
		return (1);
	}
	if ((*exe_env) && !(*exe_env)->cwd)
		return (1);
	if (ft_cd_cases(new_dir, exe_env, &home, &curpath) == -1)
		return (free(new_dir), 1);
	if (ft_before_change_dir(&canonical, &curpath, &home) == -1)
		return (free(new_dir), 1);
	res = change_directory(*exe_env, canonical);
	return (free(canonical), free(home), free(new_dir), res);
}
