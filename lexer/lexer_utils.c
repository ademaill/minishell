/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:31:45 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/12 18:44:03 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer.h"

static t_token	*regroup_next(t_token *tmp, t_token *tmp2)
{
	t_token	*to_free;

	to_free = tmp2;
	to_free->value = tmp2->value;
	ft_token_join(tmp, tmp2, 0);
	if (tmp2->next)
		tmp2->prev->next = tmp2->next;
	else
		tmp2->prev->next = NULL;
	if (tmp2->next)
		tmp2->next->prev = tmp2->prev->next;
	free(to_free->value);
	free(to_free);
	tmp2 = tmp;
	return (tmp2);
}

void	free_all(t_main *main)
{
	t_env	*tmpe;
	t_env	**env;

	if (main->env)
	{
		env = &main->env;
		tmpe = *env;
		while (*env)
		{
			tmpe = (*env)->next;
			if ((*env)->key)
				free((*env)->key);
			if ((*env)->value)
				free((*env)->value);
			free(*env);
			*env = tmpe;
		}
	}
	if (main->token)
		free_main_token(main->token);
	if (main->cmd_cpy && main->cmd_cpy[0])
		free_tab(main->cmd_cpy);
	if (main->pid)
		free(main->pid);
	free(main);
}

static void	regroup(t_token *token, t_token	*tmp, t_token *tmp2)
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
			tmp2 = regroup_next(tmp, tmp2);
		}
		tmp2 = tmp2->next;
	}
}

void	go_regroup(t_main *main)
{
	t_token	*token;
	t_token	*tmp;
	t_token	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	token = main->token;
	while (token)
	{
		if (token->type == __cmdgr)
			regroup(token, tmp, tmp2);
		token = token->next;
	}
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
