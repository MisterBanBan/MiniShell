/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:44:01 by afavier           #+#    #+#             */
/*   Updated: 2024/06/25 00:02:58 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

void	ft_strcpy(char *dst, const char *src, size_t size);
void	signal_init(void);
void	signal_child(void);
void	signal_wait(void);
void	sig_status(t_exe_builtin **new_env);
void	ft_wait_sig_part(int *sig, int *ret, int status);
int		split_input(t_input *get_input, t_cmd **cmd, t_exe_builtin **new_env);
void	ft_free_get_input(t_input **get_input);

#endif