/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:24:47 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/25 17:26:09 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_token(t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		free(token->value[i]);
		i++;
	}
	free(token->value);
	free(token);
}
