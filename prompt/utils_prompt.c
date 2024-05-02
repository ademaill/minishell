/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:03:20 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/24 09:53:50 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_token *token)
{
	t_token	*tmp;
	int	i;

	if (token)
	{
		token = ft_lstfirst(token);
		while (token)
		{
			tmp = token->next;
			i = 0;
			while (token->value[i])
			{
				free(token->value[i]);
				i++;
			}
			free(token->value);
			free(token);
			token = tmp;
		}
		free (token);
	}
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
