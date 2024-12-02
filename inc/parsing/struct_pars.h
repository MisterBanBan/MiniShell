/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_pars.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:51:52 by afavier           #+#    #+#             */
/*   Updated: 2024/07/16 23:59:40 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_PARS_H
# define STRUCT_PARS_H

int		create_file(char *name);
void	write_fd(int fd, char *input_doc);
int		fill_struct(char **input_split, t_cmd **cmd, char ***env);
int		append_cmd(t_cmd **first, char *name);
void	append_type_ope_built(int builtins, int type, int operator,
			t_cmd **cmd);
void	append_fd(int fd, t_cmd **cmd);
void	free_cmd_list(t_cmd **head);
int		open_files(char *name);
int		open_files_out(char *name);
void	order_struct_out(t_cmd **cmd_ptr);
void	rm_che(t_cmd **cmd_ptr);
void	rm_files(t_cmd **cmd_ptr);
int		search_files(t_cmd **cmd, int res, int files_in, int files_out);
void	dollars_question(t_cmd *temp, int res);
void	define_struct(t_cmd **cmd);
int		open_files_append(char *name);
void	order_struct_in(t_cmd **cmd_ptr, t_cmd *temp, t_cmd	*next, t_cmd *cmd);
int		next_pipe(t_cmd **temp, int *i);
int		files_ou_fonc_after(t_cmd **temp, t_cmd **last_open_close);

#endif