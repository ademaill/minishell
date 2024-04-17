/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:24:51 by vnavarre          #+#    #+#             */
/*   Updated: 2024/04/16 15:57:54 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_token **lst, void (*del)(void*))
{
	t_token	*list;

	if (!lst || !del)
		return ;
	list = (*lst);
	while ((*lst))
	{
		del((*lst)->value);
		list = (*lst)->next;
		free((*lst));
		(*lst) = list;
	}
	(*lst) = NULL;
}
