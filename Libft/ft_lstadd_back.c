/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:50:30 by vnavarre          #+#    #+#             */
/*   Updated: 2024/04/18 10:15:49 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*list;

	if (!new)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	list = (*lst);
	while (list->next)
		list = list->next;
	list->next = new;
}
