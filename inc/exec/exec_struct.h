/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:26:36 by nkermani          #+#    #+#             */
/*   Updated: 2024/06/17 18:54:19 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_STRUCT_H
# define EXEC_STRUCT_H

# include "struct.h"

int			exe_add_struct(t_cmd **data);
int			exec_ft_init_exe_envp(t_exe_builtin **new_env, char **envp);
t_exec_cmd	*exec_ft_fill_struct(t_cmd *data);
void		exec_free_cmd_exec(t_exec_cmd **head);
void		exec_ft_fill_last_node_cmd(t_exec_cmd **first, t_cmd *curr);
t_exec_cmd	*exec_ft_lstnew(void);
t_exec_cmd	*exec_ft_lstlast(t_exec_cmd *lst);
void		exec_ft_lstadd_back(t_exec_cmd **lst, t_exec_cmd *new_node);

#endif