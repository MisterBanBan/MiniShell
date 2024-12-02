/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtbanban <mtbanban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:49:06 by afavier           #+#    #+#             */
/*   Updated: 2024/12/02 21:03:43 by mtbanban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include "utils.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

int	g_sig;

int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_input			*get_input;
	t_cmd			*cmd;
	t_exe_builtin	*new_env;
	int				res;

	res = 0;
	line = NULL;
	get_input = NULL;
	cmd = NULL;
	if (ft_init(argc, argv, &new_env, env) == -1)
		return (-1);
	ft_loop(&line, &get_input, &cmd, &new_env);
	ft_free_usual(&line, &get_input);
	res = new_env->res;
	ft_free_break(&new_env, &cmd);
	rl_clear_history();
	ft_printf("exit\n");
	return (res);
}

int	split_input(t_input *get_input, t_cmd **cmd, t_exe_builtin **new_env)
{
	char	**input_split;
	int		error;

	if (!cmd)
		return (-1);
	input_split = ft_split_shell(get_input->input, ' ');
	if (!input_split)
		return (ft_write(2, "malloc failed\n"), -1);
	error = fill_struct(input_split, cmd, (*new_env)->name_val);
	if (error == -1)
		return (exec_ft_free_tab(input_split), -1);
	if (error == -2)
		return (exec_ft_free_tab(input_split), -2);
	define_struct(cmd);
	if (remove_quote(cmd) == -1)
		return (exec_ft_free_tab(input_split), -1);
	sig_status(new_env);
	exec_ft_free_tab(input_split);
	if (search_files(cmd, (*new_env)->res, 0, 0) == -1)
		return (-2);
	return (0);
}
