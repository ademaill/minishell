/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:24:51 by vnavarre          #+#    #+#             */
/*   Updated: 2023/11/14 10:24:36 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;

	if (!lst || !del)
		return ;
	list = (*lst);
	while ((*lst))
	{
		del((*lst)->content);
		list = (*lst)->next;
		free((*lst));
		(*lst) = list;
	}
	(*lst) = NULL;
}
