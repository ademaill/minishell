/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:31:45 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/24 15:12:50 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer.h"

int	regroup(t_token *token, t_token	*tmp, t_token *tmp2, t_token *tmp3)
{
	tmp = token;
	while (tmp->type != __cmdgr && tmp->next)
	{
		tmp = tmp->next;
	}
	tmp2 = tmp;
	while (tmp2 && tmp2->type != __pipe)
	{
		if (tmp2->type == __cmdgr && tmp != tmp2)
		{
			ft_token_join(tmp, tmp2, 0);
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

void	clear_token(t_main *main)
{
	t_token	*tmp;

	tmp = main->token;
	while (tmp)
	{
		if (tmp->value[0] == NULL)
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			free(tmp);
		}
		tmp = tmp->next;
	}
	main->token = ft_lstfirst(tmp);
}
