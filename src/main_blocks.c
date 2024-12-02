/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_blocks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:13:23 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/23 01:47:09 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include "utils.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

static void	free_all(char **line, t_input **get_input, t_cmd **cmd);
static int	white_space(char *line);

static int	ft_readline(char **line, t_input **get_input,
		t_exe_builtin **new_env)
{
	(*line) = readline("QuectoShell :");
	if (!(*line))
		return (-1);
	if (*line && (**line))
		add_history((*line));
	if (white_space(*line) == -1)
		return (ft_free_usual(line, get_input), -2);
	(*get_input) = initialize_input(ft_strdup(*line));
	if (check_quote((*get_input)) == -1)
		return (ft_free_usual(line, get_input), -2);
	if (check_synthax((*get_input), 0, 0) == -1)
	{
		ft_free_usual(line, get_input);
		(*new_env)->res = 2;
		return (ft_write(2, "error, check_syntax\n"), -2);
	}
	ft_free_get_input(get_input);
	(*get_input) = initialize_input(expand_var((*line), (*new_env)->name_val));
	if (!(*get_input))
		return (ft_free_usual(line, get_input), ft_write(2,
				"error malloc_expand_var"), -1);
	if (if_operator_no_space((*get_input), ' ', 0) == -1)
		return (ft_write(2, "error, if_operator_no_space\n"), -1);
	return (0);
}

static int	ft_quote_ok(char **line, t_input **get_input, t_cmd **cmd,
		t_exe_builtin **new_env)
{
	int	error;

	error = split_input((*get_input), cmd, new_env);
	if (error < 0)
		return (error);
	rm_files(cmd);
	rm_che(cmd);
	order_struct_in(cmd, NULL, NULL, NULL);
	order_struct_out(cmd);
	if (echo_n(cmd, 0) == -1)
		return (-1);
	neg(cmd);
	exe_add_struct(cmd);
	if (*cmd)
	{
		ft_free_usual(line, get_input);
		exec_ft_exec(cmd, new_env);
		if ((*cmd)->exec_cmd)
			exec_free_cmd_exec(&((*cmd)->exec_cmd));
		free_cmd_list(cmd);
	}
	free_all(line, get_input, cmd);
	return (0);
}

void	ft_loop(char **line, t_input **get_input, t_cmd **cmd,
		t_exe_builtin **new_env)
{
	int	checker;
	int	error;

	checker = 0;
	while (1)
	{
		signal_init();
		checker = ft_readline(line, get_input, new_env);
		sig_status(new_env);
		if (checker == -1)
			break ;
		else if (checker == -2)
			continue ;
		if (check_quote((*get_input)) == 0)
		{
			error = ft_quote_ok(line, get_input, cmd, new_env);
			if (error == -1)
				break ;
			if (error == -2)
				free_all(line, get_input, cmd);
		}
		else
			ft_free_usual(line, get_input);
	}
}

static void	free_all(char **line, t_input **get_input, t_cmd **cmd)
{
	free_cmd_list(cmd);
	ft_free_usual(line, get_input);
}

static int	white_space(char *line)
{
	int	i;

	i = 0;
	while ((line[i]))
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\r'
			&& line[i] != '\n' && line[i] != '\v' && line[i] != '\f')
			return (0);
		i++;
	}
	return (-1);
}
