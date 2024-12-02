/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:18:31 by nkermani          #+#    #+#             */
/*   Updated: 2024/06/26 14:55:15 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

void	sig_status(t_exe_builtin **new_env)
{
	if (g_sig)
	{
		g_sig = 0;
		if ((*new_env))
			(*new_env)->res = 130;
	}
}

void	ft_wait_sig_part(int *sig, int *ret, int status)
{
	*sig = WTERMSIG(status);
	if (*sig == SIGINT)
	{
		g_sig = SIGINT;
		*ret = 130;
		write(1, "\n", 1);
	}
	else if (*sig == SIGQUIT)
	{
		g_sig = SIGQUIT;
		*ret = 131;
		write(1, "Quit (code dumped)\n", 19);
	}
	else
		*ret = 128 + *sig;
}
