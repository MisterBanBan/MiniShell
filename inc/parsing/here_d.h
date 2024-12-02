/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:09:34 by afavier           #+#    #+#             */
/*   Updated: 2024/07/16 00:34:44 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_D_H
# define HERE_D_H

int		here_doc(t_cmd **cmd, char **doc, char ***env);
int		remove_quote_char(char **input_quote, char quote);

#endif