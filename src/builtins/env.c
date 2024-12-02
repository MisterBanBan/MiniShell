/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:20:24 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/16 19:41:44 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "struct.h"

static int	contains_equal(char *s)
{
	while (*s)
	{
		if (*s == '=')
			return (1);
		s++;
	}
	return (0);
}

int	ft_env(t_exe_builtin *new_env)
{
	size_t	i;

	i = 0;
	if (!new_env->envp_b)
		return (0);
	while (new_env->envp_b[i])
	{
		if (contains_equal(new_env->envp_b[i]))
			ft_putendl_fd(new_env->envp_b[i], 1);
		i++;
	}
	return (0);
}
