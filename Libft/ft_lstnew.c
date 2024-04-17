/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:31:53 by vnavarre          #+#    #+#             */
/*   Updated: 2024/04/17 11:47:00 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_token	*ft_lstnew(char **content)
{
	t_token	*elmt;

	elmt = (t_token *)malloc(sizeof(*elmt));
	if (!elmt)
		return (NULL);
	elmt->value = content;
	elmt->next = NULL;
	return (elmt);
}
