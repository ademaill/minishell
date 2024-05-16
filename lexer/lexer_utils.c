/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:31:45 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/08 11:31:46 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include "lexer.h"

int	regroup(t_token *token, t_token	*tmp, t_token *tmp2, t_token *tmp3)
{
	tmp = token;
	while(tmp->type != __cmdgr && tmp->next)
	{
		tmp = tmp->next;
	}
	tmp2 = tmp;
	while (tmp2 && tmp2->type != __pipe)
	{
		if (tmp2->type == __cmdgr && tmp != tmp2)
		{
			ft_token_join(tmp, tmp2);
			//	return (1);
			if (tmp2->next)
				tmp2->prev->next = tmp2->next;
			else
				tmp2->prev->next = NULL;
			if (tmp2->next)
				tmp2->next->prev = tmp2->prev->next;
			tmp3 = tmp2;
		}
		tmp2 = tmp2->next;
		if (tmp3)
			free(tmp3);
	}
	return (0);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
