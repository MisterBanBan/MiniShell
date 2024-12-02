/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:23:53 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 05:36:33 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "struct.h"

int		ft_echo(char *args, int fd);
int		ft_get_fd(t_cmd *current);
int		ft_pwd(void);
int		ft_cd(char *new_dir, t_exe_builtin **exe_env);
char	*get_env_value(char **envp, const char *var);
int		change_directory(t_exe_builtin *exe_env, char *curpath);
int		ft_cd_too_long(char **home, char **canonical);
int		ft_cd_cases(char *new_dir, t_exe_builtin **exe_env, char **home,
			char **curpath);
char	*canonicalize_path(char *path);
int		ft_export(char *name, t_exe_builtin **new_env);
bool	ft_check(char *name);
size_t	ft_strspn(const char *str, const char *accept);
size_t	ft_strcspn(const char *str, const char *reject);
char	*ft_strtok(char *str, const char *delim);
void	validate_export_string(char *str);
int		ft_export_append(char *name, t_exe_builtin **new_env);
void	ft_export_no_args(char ***envp);
int		ft_replace(char **name_val, t_exe_builtin **new_env);

int		ft_unset(char *name, t_exe_builtin **new_env);
int		ft_env(t_exe_builtin *new_env);
int		ft_exit(char *args, t_cmd *data, t_exe_builtin **new_env, char *cmd);
int		ft_exit_fork(char *args, t_exe_builtin **new_env);
int		exec_ft_builtin_exe(t_cmd *current, t_exe_builtin *new_env,
			char *builtin);
char	*ft_get_args(t_cmd *data, char *head, char *cmd_name);

#endif