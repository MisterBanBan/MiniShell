/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:02:15 by nkermani          #+#    #+#             */
/*   Updated: 2024/01/05 15:27:30 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*new_node;
	void	*content;

	if (!lst && !(*f) && !(*del))
		return (NULL);
	map = NULL;
	while (lst)
	{
		content = ((*f)(lst->content));
		new_node = ft_lstnew(content);
		if (!(new_node))
		{
			(*del)(content);
			ft_lstclear(&map, (*del));
			return (NULL);
		}
		ft_lstadd_back(&map, new_node);
		new_node = new_node->next;
		lst = lst->next;
	}
	return (map);
}
