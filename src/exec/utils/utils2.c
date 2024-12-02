/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 03:25:26 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/16 03:28:29 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen && s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*new_str;
	size_t	len;

	len = ft_strnlen(s, n);
	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	new_str[len] = '\0';
	return (ft_memcpy(new_str, s, len));
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next_token = NULL;
	char		*end;

	if (str == NULL)
		str = next_token;
	if (str == NULL)
		return (NULL);
	str += ft_strspn(str, delim);
	if (*str == '\0')
		return (NULL);
	end = str + ft_strcspn(str, delim);
	if (*end == '\0')
		next_token = NULL;
	else
	{
		*end = '\0';
		next_token = end + 1;
	}
	return (str);
}

size_t	ft_strspn(const char *str, const char *accept)
{
	const char	*s;
	const char	*a;
	size_t		count;

	count = 0;
	s = str;
	while (*s)
	{
		a = accept;
		while (*a)
		{
			if (*s == *a)
			{
				count++;
				break ;
			}
			a++;
		}
		if (*a == '\0')
			return (count);
		s++;
	}
	return (count);
}

size_t	ft_strcspn(const char *str, const char *reject)
{
	const char	*s;
	const char	*r;
	size_t		count;

	count = 0;
	s = str;
	while (*s)
	{
		r = reject;
		while (*r)
		{
			if (*s == *r)
				return (count);
			r++;
		}
		s++;
		count++;
	}
	return (count);
}
