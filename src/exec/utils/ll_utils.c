/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:10:52 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/14 00:50:47 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "utils.h"

void	exec_ft_swap_string(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

size_t	exec_ft_tab_len(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

char	**exec_ft_tab_dup(char **tab)
{
	char	**tab_dup;
	size_t	i;

	if (!tab || !(*tab))
		return (NULL);
	i = 0;
	tab_dup = (char **)malloc(sizeof(char *) * (exec_ft_tab_len(tab) + 1));
	if (!tab_dup)
		return (NULL);
	while (tab[i])
	{
		tab_dup[i] = ft_strdup(tab[i]);
		if (!tab_dup[i])
		{
			exec_ft_free_tab(tab_dup);
			perror("malloc failed");
			return (NULL);
		}
		i++;
	}
	tab_dup[i] = NULL;
	return (tab_dup);
}

char	**exec_ft_sort_tab(char **tab)
{
	size_t	i;
	int		swapped;

	if (!tab || (!*tab))
		return (NULL);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (tab[i + 1])
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				exec_ft_swap_string(&tab[i], &tab[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
	return (tab);
}
