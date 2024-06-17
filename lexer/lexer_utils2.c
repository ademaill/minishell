/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:54:31 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/12 18:52:10 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer.h"

void	free_main_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->value)
			free_tab(tmp->value);
		free(tmp);
	}
}

void	free_tab(char **tab)
{
	int	i;
	int	height;

	i = 0;
	height = ft_len_tab(tab);
	if (!height)
		return ;
	if (tab == NULL || *tab == NULL)
		return ;
	while (i < height)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
