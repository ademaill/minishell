/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:52:43 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/11 17:03:50 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*plst;

	if (!new)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	plst = (*lst);
	while (plst->next)
		plst = plst->next;
	plst->next = new;
}
