/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:31:53 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/10 13:58:14 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_new_node(t_token **lst, char	**content)
{
	t_token	*last;
	t_token	*new_node;

	if (lst == NULL)
		return ;
	new_node = malloc(sizeof(t_token));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->value = content;
	if ((*lst) == NULL)
	{
		(*lst) = new_node;
		new_node->prev = NULL;
	}
	else
	{
		last = ft_lstlast((*lst));
		last->next = new_node;
		new_node->prev = last;
	}
}
