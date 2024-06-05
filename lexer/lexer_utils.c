/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:31:45 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/05 18:43:23 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer.h"

/*void	free_all(t_main *main)
{
	int		i;
	t_token	*tmp;
	t_env	*tmpe;


	if (main->env)
	{
		i = 0;
		while (main->env)
		{
			tmpe = main->env;
			main->env = main->env->next;
			free(tmpe->key);
			free(tmpe->value);
			free(tmpe);
		}
		free(main->token);
	}
	if (main->token)
	{
		i = 0;
		while (main->token)
		{
			tmp = main->token;
			main->token = main->token->next;
			free_tab(tmp->value);
			free(tmp);
		}
		free(main->token);
	}
	if (main->pid)
		free(main->pid);
	free(main);
}*/

void	regroup(t_token *token, t_token	*tmp, t_token *tmp2, t_token *tmp3)
{
	tmp = token;
	if (!tmp)
		return ;
	while (tmp->next && tmp->type != __cmdgr)
	{
		tmp = tmp->next;
	}
	tmp2 = tmp;
	while (tmp2 && tmp2->type != __pipe)
	{
		if (tmp2->type == __cmdgr && tmp != tmp2)
		{
			ft_token_join(tmp, tmp2, 0);
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
}

void	go_regroup(t_main *main)
{
	t_token *token;
	t_token	*tmp;
	t_token	*tmp2;
	t_token	*tmp3;

	tmp = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	token = main->token;
	while(token)
	{
		if (token->type == __cmdgr)
			regroup(token, tmp, tmp2, tmp3);
		token = token->next;
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
