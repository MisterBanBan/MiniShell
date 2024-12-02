/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:40:29 by afavier           #+#    #+#             */
/*   Updated: 2024/07/16 00:30:10 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>

static int	append_operator(char **input_split, t_cmd **cmd, size_t *i,
				char ***env);
static int	append_builtins(char **input_split, t_cmd **cmd, size_t i);

int	fill_struct(char **input_split, t_cmd **cmd, char ***env)
{
	size_t	i;

	i = 0;
	if (!input_split)
		return (-1);
	while (input_split[i] != NULL)
	{
		if (append_cmd(cmd, input_split[i]) == -1)
			return (-1);
		append_type_ope_built(NO_BUILTINS, COMMAND, NO_OPERATOR, cmd);
		if (append_operator(input_split, cmd, &i, env) == -1)
			return (-2);
		if (append_builtins(input_split, cmd, i) == -1)
			return (-1);
		if (input_split[i] != NULL)
			i++;
	}
	return (0);
}

static int	append_operator(char **input_split, t_cmd **cmd, size_t *i,
		char ***env)
{
	if (input_split[(*i)][0] == '<' && input_split[(*i)][1] == '\0')
		append_type_ope_built(NO_BUILTINS, OPERATOR, CHEVRON_INPUT, cmd);
	else if (input_split[(*i)][0] == '>' && input_split[(*i)][1] == '\0')
		append_type_ope_built(NO_BUILTINS, OPERATOR, CHEVRON_OUTPUT, cmd);
	else if (input_split[(*i)][0] != '\0' && input_split[(*i)][1] != '\0'
		&& input_split[(*i)][0] == '<' && input_split[(*i)][1] == '<')
	{
		append_type_ope_built(NO_BUILTINS, OPERATOR, HERE_DOC, cmd);
		if (here_doc(cmd, &input_split[(*i) + 1], env) == -1)
			return (-1);
		(*i)++;
	}
	else if (input_split[(*i)][0] != '\0' && input_split[(*i)][1] != '\0'
		&& input_split[(*i)][0] == '>' && input_split[(*i)][1] == '>')
		append_type_ope_built(NO_BUILTINS, OPERATOR, APPEND, cmd);
	else if (input_split[(*i)][0] == '|')
		append_type_ope_built(NO_BUILTINS, OPERATOR, PIPE, cmd);
	return (0);
}

static int	append_builtins(char **input_split, t_cmd **cmd, size_t i)
{
	if (ft_strcmp(input_split[i], "echo") == 0)
		append_type_ope_built(ECHO, BUILTIN, NO_OPERATOR, cmd);
	else if (ft_strcmp(input_split[i], "pwd") == 0)
		append_type_ope_built(PWD, BUILTIN, NO_OPERATOR, cmd);
	else if (ft_strcmp(input_split[i], "cd") == 0)
		append_type_ope_built(CD, BUILTIN, NO_OPERATOR, cmd);
	else if (ft_strcmp(input_split[i], "env") == 0)
		append_type_ope_built(ENV, BUILTIN, NO_OPERATOR, cmd);
	else if (ft_strcmp(input_split[i], "export") == 0)
		append_type_ope_built(EXPORT, BUILTIN, NO_OPERATOR, cmd);
	else if (ft_strcmp(input_split[i], "unset") == 0)
		append_type_ope_built(UNSET, BUILTIN, NO_OPERATOR, cmd);
	else if (ft_strcmp(input_split[i], "exit") == 0)
		append_type_ope_built(EXIT, BUILTIN, NO_OPERATOR, cmd);
	return (0);
}
