/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:36:04 by afavier           #+#    #+#             */
/*   Updated: 2024/07/17 00:49:09 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "struct.h"

void	path(char *append);
char	*find_path(char ***env, char *path);
char	*append_expand(char *input, char *append, size_t start, size_t end);
char	*expand_var(char *input, char ***env);
void	expand_num(char **in, size_t *i);

#endif