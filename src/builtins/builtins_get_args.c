/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_get_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:10:46 by nkermani          #+#    #+#             */
/*   Updated: 2024/06/18 22:33:09 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"

char	*ft_get_args(t_cmd *data, char *head, char *cmd_name)
{
	char	*res;

	res = NULL;
	if (!ft_strcmp(data->name, cmd_name) && !ft_strcmp(head, cmd_name))
	{
		return (NULL);
	}
	else if (!ft_strcmp(data->name, cmd_name) && ft_strcmp(head, cmd_name))
	{
		res = ft_substr(head, ft_strlen(data->name) + 1, ft_strlen(head)
				- ft_strlen(data->name));
		return (res);
	}
	else
		return (NULL);
}
