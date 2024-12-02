/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:43:37 by nkermani          #+#    #+#             */
/*   Updated: 2023/12/13 14:36:24 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*roamer;
	t_list	*next;

	if (!lst && !(*del))
		return ;
	roamer = *lst;
	while (roamer)
	{
		next = roamer->next;
		ft_lstdelone(roamer, del);
		roamer = next;
	}
	*lst = NULL;
}
