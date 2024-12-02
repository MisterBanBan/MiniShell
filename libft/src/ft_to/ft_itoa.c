/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:10:36 by nkermani          #+#    #+#             */
/*   Updated: 2023/12/13 14:38:21 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	intlen(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	make_res(char *res, int len, int i, int n)
{
	while (len-- > i)
	{
		if (n < 0)
		{
			res[len] = '0' + n % 10 * (-1);
			n = n / 10;
		}
		else
		{
			res[len] = '0' + n % 10;
			n = n / 10;
		}
	}
}

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*res;

	len = intlen(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!(res))
		return (NULL);
	res[len] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		i = 1;
	}
	else
		i = 0;
	make_res(res, len, i, n);
	return (res);
}
