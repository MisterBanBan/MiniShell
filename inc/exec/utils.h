/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:24:20 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/18 23:16:38 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"

void	after_split_back_to_pos_char(char ***tab);
void	ft_whitespace_to_neg(char **str);
void	ft_whitespace_back_to_pos(char **str);
int		ft_update_env(t_exe_builtin **new_env);
char	**ft_get_name_val(char *name);
bool	ft_check_in_env(char **name_val, char ***new_env_name);
int		ft_init(int argc, char **argv, t_exe_builtin **new_env, char **envp);

size_t	ft_strnlen(const char *s, size_t maxlen);
char	*ft_strndup(const char *s, size_t n);
void	ft_write(int fd, char *str);

char	*exec_ft_strcat(char *dest, const char *src);
char	*exec_ft_strcpy(char *dest, const char *src);
void	*exec_ft_realloc(void *ptr, size_t new_size);

void	exec_ft_free_tab(char **tab);
void	ft_free_break(t_exe_builtin **new_env, t_cmd **cmd);
void	ft_free_usual(char **line, t_input **get_input);
void	ft_free_exit_child(t_cmd **data, t_exe_builtin *new_env);

void	execve_and_exit(char *cmd, t_cmd **data, t_cmd *current,
			t_exe_builtin *new_env);
void	builtin_and_exit(char *cmd, t_cmd **data, t_cmd *current,
			t_exe_builtin *new_env);

void	exec_ft_swap_string(char **s1, char **s2);
size_t	exec_ft_tab_len(char **tab);
char	**exec_ft_tab_dup(char **tab);
char	**exec_ft_sort_tab(char **tab);
char	**exec_ft_tab_dup_names(char **tab);
char	**exec_ft_tab_dup_values(char **tab);

t_cmd	*exec_ft_go_to_first(t_cmd *data);
t_cmd	*exec_ft_go_to_last(t_cmd *data);
t_cmd	*exec_ft_go_to_next_type(t_cmd *data, enum e_type type);
t_cmd	*exec_ft_go_to_last_type(t_cmd *data, enum e_type type);

#endif