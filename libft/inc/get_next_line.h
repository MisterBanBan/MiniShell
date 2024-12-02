/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:59:45 by nkermani          #+#    #+#             */
/*   Updated: 2024/01/06 21:23:14 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list_gnl
{
	char				*content;
	struct s_list_gnl	*next;
}						t_list_gnl;

char					*get_next_line(int fd);
int						found_newline(t_list_gnl *stash);
t_list_gnl				*ft_lst_get_last(t_list_gnl *stash);
int						read_and_stash(int fd, t_list_gnl **stash);
int						add_to_stash(t_list_gnl **stash, char *buf, int readed);
void					extract_line(t_list_gnl *stash, char **line);
void					generate_line(char **line, t_list_gnl *stash);
int						clean_stash(t_list_gnl **stash);
size_t					gnl_strlen(const char *s);
void					free_stash(t_list_gnl *stash);

#endif