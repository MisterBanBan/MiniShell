/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:04:02 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/14 01:10:43 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "exec_struct.h"
# include "struct.h"

int		ft_init(int argc, char **argv, t_exe_builtin **new_env, char **envp);
void	ft_loop(char **line, t_input **get_input, t_cmd **cmd,
			t_exe_builtin **new_env);
int		exec_ft_close_files(t_cmd *data);
int		exec_ft_close_files_children(t_cmd **data);

int		exec_ft_exec(t_cmd **data, t_exe_builtin **new_env);
int		exec_ft_cmd_exec(t_cmd *data, t_exe_builtin *new_env);

int		exec_ft_pipe(t_cmd **data, t_cmd *current);
int		exec_ft_dup2_infile(t_cmd **data, t_cmd *current);
int		exec_ft_dup2_outfile(t_cmd **data, t_cmd *current);
int		exec_reset_pipefd(t_cmd **data);
int		exec_exec_ft_execve(char *cmd, t_cmd *data, char **envp);
int		reset_std_fd(int *tmp_fd);
pid_t	exec_ft_fork(t_cmd **data, t_cmd *current, t_exe_builtin *new_env,
			pid_t pid);
int		exec_ft_cmd_exec_builtin(t_cmd **data, t_exe_builtin *new_env,
			t_cmd *curr, pid_t *pid);
int		exec_ft_no_fork_builtin_exe(t_cmd *data, t_cmd *current,
			t_exe_builtin *new_env, int **tmp_fd);
pid_t	exec_ft_fork_builtin(t_cmd **data, t_cmd *current,
			t_exe_builtin *new_env, pid_t pid);

#endif