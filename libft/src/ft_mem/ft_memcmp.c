/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:50:51 by nkermani          #+#    #+#             */
/*   Updated: 2023/12/13 14:36:51 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*mem_str1;
	unsigned char	*mem_str2;
	size_t			i;

	mem_str1 = (unsigned char *)s1;
	mem_str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((mem_str1[i] == mem_str2[i]) && (i < (n - 1)))
		i++;
	return (mem_str1[i] - mem_str2[i]);
}
