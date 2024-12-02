/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:33:39 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/16 23:31:19 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"

char	**exec_ft_tab_dup_names(char **tab)
{
	char	**tab_dup;
	size_t	i;
	char	*eq_pos;

	if (!tab || !(*tab))
		return (NULL);
	i = 0;
	tab_dup = (char **)malloc(sizeof(char *) * (exec_ft_tab_len(tab) + 1));
	if (!tab_dup)
		return (NULL);
	while (tab[i])
	{
		eq_pos = ft_strchr(tab[i], '=');
		tab_dup[i] = ft_strndup(tab[i], (eq_pos - tab[i]));
		if (!tab_dup[i])
		{
			exec_ft_free_tab(tab_dup);
			perror("malloc failed");
			return (NULL);
		}
		i++;
	}
	tab_dup[i] = NULL;
	return (tab_dup);
}

char	**exec_ft_tab_dup_values(char **tab)
{
	char	**tab_dup;
	size_t	i;
	char	*eq_pos;

	if (!tab || !(*tab))
		return (NULL);
	i = 0;
	tab_dup = (char **)malloc(sizeof(char *) * (exec_ft_tab_len(tab) + 1));
	if (!tab_dup)
		return (NULL);
	while (tab[i])
	{
		eq_pos = ft_strchr(tab[i], '=');
		tab_dup[i] = ft_strdup(eq_pos + 1);
		if (!tab_dup[i])
		{
			exec_ft_free_tab(tab_dup);
			perror("malloc failed");
			return (NULL);
		}
		i++;
	}
	tab_dup[i] = NULL;
	return (tab_dup);
}

int	ft_init(int argc, char **argv, t_exe_builtin **new_env, char **envp)
{
	if (error_args_and_dup_env(argc, argv) == -1)
		return (-1);
	if (exec_ft_init_exe_envp(new_env, envp) == -1)
		return (-1);
	return (0);
}
