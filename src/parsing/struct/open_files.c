/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:23:58 by afavier           #+#    #+#             */
/*   Updated: 2024/07/18 23:26:17 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

int	open_files(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (ft_write(2, "Permission denied\n"), -1);
	return (fd);
}

int	open_files_out(char *name)
{
	int	fd;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_write(2, "Permission denied\n"), -1);
	return (fd);
}

int	open_files_append(char *name)
{
	int	fd;

	fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (ft_write(2, "Permission denied\n"), -1);
	return (fd);
}
