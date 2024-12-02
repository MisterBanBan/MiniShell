/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_add_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:09:27 by nkermani          #+#    #+#             */
/*   Updated: 2024/06/27 12:42:40 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec_struct.h"
#include "struct.h"

int	exe_add_struct(t_cmd **data)
{
	if (!*data)
		return (0);
	(*data)->exec_cmd = exec_ft_fill_struct(*data);
	if (!(*data)->exec_cmd)
		return (-1);
	return (0);
}
