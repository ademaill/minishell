/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:16:01 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/18 10:17:26 by ademaill         ###   ########.fr       */
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
