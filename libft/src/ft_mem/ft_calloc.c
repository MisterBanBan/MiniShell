/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:45:42 by nkermani          #+#    #+#             */
/*   Updated: 2023/12/13 14:36:47 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (!nmemb || !size)
		return (malloc(0));
	if ((nmemb > (SIZE_MAX / size)))
		return (NULL);
	mem = malloc(nmemb * size);
	if (!mem)
		return (mem);
	ft_bzero(mem, (nmemb * size));
	return (mem);
}
