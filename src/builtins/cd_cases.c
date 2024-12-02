/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cases.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:28:04 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 23:28:32 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "struct.h"
#include "utils.h"
#include <linux/limits.h>

static int	ft_cd_else_one(t_exe_builtin **exe_env, char **tmp, char **home)
{
	(*tmp) = ft_strjoin((*exe_env)->cwd, "/");
	if (!(*tmp))
	{
		ft_write(2, "malloc failed\n");
		free((*home));
		return (-1);
	}
	return (0);
}

static int	ft_cd_else_two(char **new_dir, char **tmp, char **home,
		char **curpath)
{
	(*curpath) = ft_strjoin(*tmp, *new_dir);
	free(*tmp);
	if (!(*curpath))
	{
		ft_write(2, "malloc failed\n");
		free((*home));
		return (-1);
	}
	return (0);
}

int	ft_cd_cases(char *new_dir, t_exe_builtin **exe_env, char **home,
		char **curpath)
{
	char	*tmp;

	if (!new_dir && (*home))
	{
		(*curpath) = ft_strdup((*home));
		if (!(*curpath))
			ft_write(2, "malloc failed\n");
	}
	else if (new_dir && new_dir[0] == '/')
	{
		(*curpath) = ft_strdup(new_dir);
		if (!(*curpath))
			ft_write(2, "malloc failed\n");
	}
	else
	{
		if (ft_cd_else_one(exe_env, &tmp, home) == -1)
			return (-1);
		if (ft_cd_else_two(&new_dir, &tmp, home, curpath) == -1)
			return (-1);
	}
	return (0);
}
