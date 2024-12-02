/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:20:30 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 23:27:40 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"
#include <readline/history.h>
#include <readline/readline.h>

static int	ft_isnumeric(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void	ft_exit_no_args_fork(char *args, t_exe_builtin **new_env, int *res)
{
	*res = (*new_env)->res;
	if (!args)
	{
		ft_printf("exit\n");
		rl_clear_history();
		exit(*res);
	}
}

static int	ft_exit_end_fork(char *args, int *res)
{
	ft_printf("exit\n");
	free(args);
	rl_clear_history();
	exit((*res));
	return ((*res));
}

int	ft_exit_fork(char *args, t_exe_builtin **new_env)
{
	int		res;
	char	**args_tab;

	ft_whitespace_back_to_pos(&args);
	ft_exit_no_args_fork(args, new_env, &res);
	args_tab = ft_split_shell(args, ' ');
	if (!args_tab)
		return (ft_write(2, "malloc failed\n"), -1);
	if (args_tab[0] && !ft_isnumeric(args_tab[0]))
	{
		ft_write(2, "Quectoshell: exit: numeric argument required\n");
		res = 2;
	}
	else if (args_tab[1])
		return (exec_ft_free_tab(args_tab), free(args), ft_write(2,
				"Quectoshell: exit: too many arguments\n"), 1);
	else if (args_tab[0])
		res = ft_atoi(args_tab[0]) % 256;
	exec_ft_free_tab(args_tab);
	return (ft_exit_end_fork(args, &res));
}
