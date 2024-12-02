/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:58:39 by nkermani          #+#    #+#             */
/*   Updated: 2024/01/06 21:22:51 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list_gnl	*stash;
	char				*line;

	if (fd < 0)
		return (NULL);
	if (BUFFER_SIZE <= 0)
		return (free_stash(stash), stash = NULL, NULL);
	line = NULL;
	read_and_stash(fd, &stash);
	extract_line(stash, &line);
	if (line)
	{
		clean_stash(&stash);
		if (stash == NULL)
			return (free(line), NULL);
		if (line[0] == '\0')
			return (free_stash(stash), stash = NULL, free(line), NULL);
	}
	else
	{
		free_stash(stash);
		stash = NULL;
	}
	return (line);
}

int	read_and_stash(int fd, t_list_gnl **stash)
{
	char	*buffer;
	int		count_read;

	count_read = 1;
	while (!found_newline(*stash) && count_read != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return (free_stash(*stash), *stash = NULL, -1);
		count_read = (int)read(fd, buffer, BUFFER_SIZE);
		if ((*stash == NULL && count_read == 0) || count_read == -1)
			return (free(buffer), free_stash(*stash), *stash = NULL, -1);
		buffer[count_read] = '\0';
		if (add_to_stash(stash, buffer, count_read) == -1)
			return (free(buffer), free_stash(*stash), *stash = NULL, -1);
		free(buffer);
	}
	return (1);
}

int	add_to_stash(t_list_gnl **stash, char *buffer, int count_read)
{
	size_t		i;
	t_list_gnl	*last;
	t_list_gnl	*new_node;

	new_node = malloc(sizeof(t_list_gnl));
	if (new_node == NULL)
		return (-1);
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (count_read + 1));
	if (new_node->content == NULL)
		return (free(new_node), -1);
	i = 0;
	while (buffer[i] && (int)i < count_read)
	{
		new_node->content[i] = buffer[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
		return (*stash = new_node, 1);
	last = ft_lst_get_last(*stash);
	last->next = new_node;
	return (1);
}

void	extract_line(t_list_gnl *stash, char **line)
{
	size_t	i;
	size_t	j;

	if (stash == NULL)
		return ;
	generate_line(line, stash);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

int	clean_stash(t_list_gnl **stash)
{
	t_list_gnl	*last;
	t_list_gnl	*clean_node;
	size_t		index[2];

	clean_node = malloc(sizeof(t_list_gnl));
	if (clean_node == NULL)
		return (free_stash(*stash), *stash = NULL, -1);
	clean_node->next = NULL;
	last = ft_lst_get_last(*stash);
	index[0] = 0;
	while (last->content[index[0]] && last->content[index[0]] != '\n')
		index[0]++;
	if (last->content[index[0]] && last->content[index[0]] == '\n')
		index[0]++;
	clean_node->content = malloc(sizeof(char) * ((gnl_strlen(last->content)
					- index[0]) + 1));
	if (clean_node->content == NULL)
		return (free(clean_node), free_stash(*stash), *stash = NULL, -1);
	index[1] = 0;
	while (last->content[index[0]])
		clean_node->content[index[1]++] = last->content[index[0]++];
	clean_node->content[index[1]] = '\0';
	free_stash(*stash);
	*stash = clean_node;
	return (1);
}
