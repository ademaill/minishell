/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:03:20 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/06 14:50:09 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fullexit(t_token *token, char *prompt)
{
	t_token	*tmp;
	int		i;

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
	free(prompt);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
