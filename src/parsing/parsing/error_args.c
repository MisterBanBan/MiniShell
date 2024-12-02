/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:40:20 by afavier           #+#    #+#             */
/*   Updated: 2024/07/18 23:28:00 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

int	error_args_and_dup_env(int argc, char **argv)
{
	if (!argv)
		return (-1);
	if (argc > 1)
	{
		ft_write(2, "Please just type ./minishell\n");
		return (-1);
	}
	return (0);
}
