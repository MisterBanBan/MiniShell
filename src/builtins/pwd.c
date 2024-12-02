/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:20:39 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/23 01:58:46 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "struct.h"
#include "utils.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
		ft_printf("%s\n", cwd);
	else
	{
		ft_write(2, "getcwd failed()\n");
		free(cwd);
		return (1);
	}
	free(cwd);
	return (0);
}
