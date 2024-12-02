/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:37:09 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 23:17:57 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"

void	ft_export_no_args(char ***envp)
{
	int	i;

	i = 0;
	while (envp[0] && envp[1] && envp[0][i])
	{
		if (envp[1][i])
			ft_printf("declare -x %s=\"%s\"\n", envp[0][i], envp[1][i]);
		else
			ft_printf("declare -x %s\n", envp[0][i]);
		i++;
	}
}

static int	ft_get_name_no_val(char ***res, char *name)
{
	(*res)[0] = ft_strdup(name);
	if (!(*res)[0])
		return (free((*res)), ft_write(2, "malloc failed\n"), -1);
	(*res)[1] = NULL;
	return (0);
}

char	**ft_get_name_val(char *name)
{
	char	**res;
	char	*eq_pos;

	if (!name)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * 2);
	if (!res)
		return (ft_write(2, "malloc failed\n"), NULL);
	eq_pos = ft_strchr(name, '=');
	if (!eq_pos)
	{
		if (ft_get_name_no_val(&res, name) == -1)
			return (NULL);
	}
	else
	{
		res[0] = ft_strndup(name, (eq_pos - name));
		if (!res[0])
			return (free(res), ft_write(2, "malloc failed\n"), NULL);
		res[1] = ft_strdup(eq_pos + 1);
		if (!res[1])
			return (free(res[0]), free(res), ft_write(2, "malloc failed\n"),
				NULL);
	}
	return (res);
}

bool	ft_check_in_env(char **name_val, char ***new_env_name)
{
	int	i;

	i = 0;
	while (new_env_name[0] && new_env_name[0][i])
	{
		if (!ft_strcmp(name_val[0], new_env_name[0][i]))
			return (true);
		i++;
	}
	return (false);
}
