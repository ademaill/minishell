/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:46:34 by vnavarre          #+#    #+#             */
/*   Updated: 2024/04/17 10:09:44 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_token	*ft_lstmap(t_token *lst, void *(*f)(void *), void (*del)(void *))
{
	t_token	*list;
	void	*new_ct;
	t_token	*new_elmt;

	if (!lst || !f || !del)
		return (NULL);
	list = NULL;
	while (lst)
	{
		new_ct = f(lst->value);
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
