/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:32:59 by vnavarre          #+#    #+#             */
/*   Updated: 2024/04/16 15:58:06 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_token *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->value);
	free(lst);
}
