/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:02:12 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/11 15:46:35 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

t_token	*ft_lstnew(char **content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->value = content;
	new->next = NULL;
	return (new);
}
