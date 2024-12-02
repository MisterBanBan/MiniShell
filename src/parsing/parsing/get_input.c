/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:07:03 by afavier           #+#    #+#             */
/*   Updated: 2024/07/18 23:26:07 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

t_input	*initialize_input(char *input)
{
	t_input	*init_input;
	size_t	len;

	len = 0;
	init_input = malloc(sizeof(t_input));
	if (!init_input)
	{
		ft_write(2, "Error malloc input\n");
		return (free(input), NULL);
	}
	len = ft_strlen(input);
	init_input->input = input;
	init_input->len = len;
	return (init_input);
}
