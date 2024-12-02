/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:01:24 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/16 22:37:42 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	dest_len;
	char	*dest;

	i = 0;
	if (!s)
		return (NULL);
	dest_len = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * (dest_len + 1));
	if (!(dest))
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
