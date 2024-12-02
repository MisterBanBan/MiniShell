/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_canon.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:48:29 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 23:17:51 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "struct.h"
#include "utils.h"
#include <linux/limits.h>

static int	canonicalize_path_loop_sub_dot_nothing(char ***components, int *i)
{
	if ((ft_strcmp((*components)[*i], ".") == 0)
		|| (ft_strlen((*components)[*i]) == 0))
	{
		*i += 1;
		return (1);
	}
	return (0);
}

static int	canonicalize_path_loop_sub_dot_dot(char ***components,
		char **canonical_path, int *i)
{
	int	j;

	if (ft_strcmp((*components)[*i], "..") == 0)
	{
		j = ft_strlen(*canonical_path) - 1;
		while (j >= 0 && (*canonical_path)[j] != '/')
			j--;
		if (j >= 0)
			(*canonical_path)[j] = '\0';
		else
			(*canonical_path)[0] = '\0';
		return (1);
	}
	return (0);
}

static int	canonicalize_path_loop_else(char ***components,
		char **canonical_path, char **tmp, int i)
{
	*tmp = ft_strjoin(*canonical_path, "/");
	if (!*tmp)
	{
		free(*canonical_path);
		exec_ft_free_tab(*components);
		return (-1);
	}
	free(*canonical_path);
	*canonical_path = ft_strjoin(*tmp, (*components)[i]);
	free(*tmp);
	if (!*canonical_path)
	{
		exec_ft_free_tab(*components);
		return (-1);
	}
	return (0);
}

static void	canonicalize_path_loop(char ***components, char **canonical_path,
		char **tmp)
{
	int	i;

	i = 0;
	while ((*components)[i])
	{
		if (canonicalize_path_loop_sub_dot_nothing(components, &i) == 1)
			continue ;
		if (canonicalize_path_loop_sub_dot_dot(components, canonical_path,
				&i) == 1)
			;
		else if (canonicalize_path_loop_else(components, canonical_path, tmp,
				i) == -1)
			return ;
		i++;
	}
}

char	*canonicalize_path(char *path)
{
	char	**components;
	char	*canonical_path;
	char	*tmp;

	components = ft_split(path, '/');
	if (!components)
	{
		ft_write(2, "malloc failed\n");
		return (NULL);
	}
	canonical_path = ft_strdup("/");
	if (!canonical_path)
	{
		ft_write(2, "malloc failed\n");
		return (exec_ft_free_tab(components), NULL);
	}
	canonicalize_path_loop(&components, &canonical_path, &tmp);
	if (ft_strlen(canonical_path) == 0)
	{
		free(canonical_path);
		canonical_path = ft_strdup("/");
		if (!canonical_path)
			return (ft_write(2, "malloc failed\n"), NULL);
	}
	return (exec_ft_free_tab(components), canonical_path);
}
