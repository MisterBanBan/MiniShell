/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:20:30 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 23:27:31 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"
#include <readline/history.h>
#include <readline/readline.h>

int	ft_isnumeric(const char *str)
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

static void	ft_exit_no_args(char *args, t_cmd *data, t_exe_builtin **new_env,
		int *res)
{
	(void)data;
	*res = (*new_env)->res;
	if (!args)
	{
		ft_printf("exit\n");
		rl_clear_history();
		exec_free_cmd_exec(&data->exec_cmd);
		ft_free_break(new_env, &data);
		exit(*res);
	}
}

static int	ft_exit_end(char *args, t_cmd *data, t_exe_builtin **new_env,
		int *res)
{
	ft_printf("exit\n");
	exec_free_cmd_exec(&data->exec_cmd);
	ft_free_break(new_env, &data);
	free(args);
	rl_clear_history();
	exit((*res));
	return ((*res));
}

int	ft_exit(char *args, t_cmd *data, t_exe_builtin **new_env, char *cmd)
{
	int		res;
	char	**args_tab;

	if (cmd)
		free(cmd);
	ft_whitespace_back_to_pos(&args);
	ft_exit_no_args(args, data, new_env, &res);
	args_tab = ft_split_shell(args, ' ');
	if (!args_tab)
		return (ft_write(2, "malloc failed\n"), free(args), -1);
	if (args_tab[0] && !ft_isnumeric(args_tab[0]))
	{
		ft_write(2, "Quectoshell: exit: numeric argument required\n");
		res = 2;
	}
	else if (args_tab[1])
	{
		ft_write(2, "Quectoshell: exit: too many arguments\n");
		return (free(args), exec_ft_free_tab(args_tab), 1);
	}
	else if (args_tab[0])
		res = ft_atoi(args_tab[0]) % 256;
	exec_ft_free_tab(args_tab);
	return (ft_exit_end(args, data, new_env, &res));
}
