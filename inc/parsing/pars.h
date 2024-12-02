/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:04:08 by afavier           #+#    #+#             */
/*   Updated: 2024/07/17 00:44:48 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
# define PARS_H

t_input	*initialize_input(char *input);
int		append_space_chevron(t_input *get_input, char *append, size_t start,
			int len_append);
int		if_operator_no_space(t_input *get_input, char quote, size_t i);
int		check_quote(t_input *get_input);
int		check_synthax(t_input *get_input, size_t len, size_t i);
int		if_pipe_space(t_input *get_input, size_t *i);
int		echo_n(t_cmd **cmd_ptr, int i);
void	neg(t_cmd **cmd_ptr);
int		error_args_and_dup_env(int argc, char **argv);
char	**ft_split_shell(char const *s, char c);
int		remove_dollars(char **input_dollars, size_t start);
int		skip_white_spaces(char const *s, ssize_t *i);
void	*total_free_shell(char **str2d);
int		remove_quote(t_cmd **cmd);
int		malloc_start(int i, char **start, t_cmd *temp);
int		if_tab_split_null(t_cmd *temp, char **tab_split, int *j, char *start);
int		check_pipe_after(t_input *get_inp, int i, int len);
int		space_append(t_input *get_input, size_t *i);
int		if_space(t_input *get_input, size_t *i);
void	check_quote_synthax(t_input *get_input, size_t *i);

#endif