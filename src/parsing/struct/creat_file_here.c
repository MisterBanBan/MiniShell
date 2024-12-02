/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_file_here.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:40:13 by afavier           #+#    #+#             */
/*   Updated: 2024/07/18 23:26:42 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"

int	create_file(char *name)
{
	int	fd;
	int	urandom_fd;

	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd < 0)
		return (-1);
	read(urandom_fd, name, 5);
	name[5] = '\0';
	if (close(urandom_fd) == -1)
		return (ft_write(2, "error close fd\n"), -1);
	fd = open(name, O_RDWR | O_CREAT, 0666);
	if (fd < 0)
	{
		perror("open");
		ft_write(2, "error fd\n");
		return (-1);
	}
	return (fd);
}

void	write_fd(int fd, char *input_doc)
{
	write(fd, input_doc, ft_strlen(input_doc));
	write(fd, "\n", 1);
}
