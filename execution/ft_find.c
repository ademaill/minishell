/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:10:45 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/13 18:24:27 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_token	*ft_find_cmdgr(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (token->prev && token->prev->type != __pipe)
		token = token->prev;
	while (token && token->type != __pipe)
	{
		if (token->type == __cmdgr)
			return (token);
		token = token->next;
	}
	return (tmp);
}

static t_token	*ft_find_else(t_token *token, int *i, int pipecount)
{
	while (token)
	{
		if (token->type == __pipe)
			(*i)++;
		if (token->type == __pipe && (*i) == pipecount - 1)
			return (token->next);
		token = token->next;
	}
	return (NULL);
}

t_token	*ft_find(t_token *token, bool last, int pipecount)
{
	int		i;
	t_token	*head;
	t_token	*tmp;

	i = 0;
	head = token;
	tmp = NULL;
	if (!last)
	{
		while (token)
		{
			if (token->type == __pipe)
				i++;
			if (token->type == __pipe && i == pipecount)
				return (token->prev);
			token = token->next;
		}
	}
	else
	{
		tmp = ft_find_else(token, &i, pipecount);
		if (tmp != NULL)
			return (tmp);
	}
	return (head);
}
