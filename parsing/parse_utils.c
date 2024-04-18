/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:36:12 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/18 11:44:54 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	str_modify(t_token *token)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 1;
	str = token->value[0];
	while (str[i])
	{
		tmp[i - 1] = str[i];
		i++;
	}
	token->value[0][0] = str[0];
	token->value[0][1] = '\0';
	token->value[1] = tmp;
	token->value[2] = NULL;
}
