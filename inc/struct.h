/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:55:06 by afavier           #+#    #+#             */
/*   Updated: 2024/07/15 23:33:15 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "ft_printf.h"
# include "ft_printf_fd.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

extern int					g_sig;

typedef enum e_quote
{
	quote_simple,
	quote_double,
}							t_quote;

enum						e_builtins
{
	ECHO = 0,
	PWD = 1,
	CD = 2,
	ENV = 3,
	EXPORT = 4,
	UNSET = 5,
	EXIT = 6,
	NO_BUILTINS = 7,
};

enum						e_type
{
	COMMAND = 0,
	ARGUMENT = 1,
	IN_FILE = 2,
	OUT_FILE = 3,
	OPERATOR = 4,
	BUILTIN = 5,
	NO_TYPE = 6,
};

enum						e_operators
{
	PIPE = 0,
	CHEVRON_INPUT = 1,
	CHEVRON_OUTPUT = 2,
	HERE_DOC = 3,
	APPEND = 4,
	NO_OPERATOR = 5,
};

typedef struct s_history_entry
{
	char					*command;
	struct s_history_entry	*next;
}							t_history_entry;

typedef struct s_cmd
{
	char					*name;
	enum e_builtins			builtin;
	enum e_type				type;
	enum e_operators		op;
	int						fd;
	bool					err;
	bool					quote;
	struct s_cmd			*next;
	struct s_cmd			*last;
	struct s_exec_cmd		*exec_cmd;
	struct s_exec_cmd		*head;
	int						pfd[2];
	int						tmpfd;
}							t_cmd;

typedef struct s_input
{
	char					*input;
	size_t					len;
}							t_input;

typedef struct s_exe_builtin
{
	int						res;
	char					*oldpwd;
	char					*cwd;
	char					**envp_b;
	char					***name_val;
}							t_exe_builtin;

typedef struct s_exec_cmd
{
	char					*cmd;
	struct s_exec_cmd		*next;
	bool					quote;
}							t_exec_cmd;

#endif