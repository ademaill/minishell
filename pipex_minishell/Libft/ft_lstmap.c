/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:46:34 by vnavarre          #+#    #+#             */
/*   Updated: 2023/11/09 18:21:18 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	void	*new_ct;
	t_list	*new_elmt;

	if (!lst || !f || !del)
		return (NULL);
	list = NULL;
	while (lst)
	{
		new_ct = f(lst->content);
		new_elmt = ft_lstnew(new_ct);
		if (!new_elmt)
		{
			del(new_ct);
			ft_lstclear(&list, del);
			return (list);
		}
		ft_lstadd_back(&list, new_elmt);
		lst = lst->next;
	}
	return (list);
}
