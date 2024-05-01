/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:36:19 by vnavarre          #+#    #+#             */
/*   Updated: 2024/04/27 16:44:45 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"


static t_list	*ft_lst_new(void *content)
{
	t_list	*new_node;

	new_node = ft_calloc(1, sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node -> content = content;
	new_node -> next = NULL;
	return (new_node);
}

static void	ft_lst_add_back(t_list **lst, t_list *new)
{
	t_list	*curr_node;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr_node = *lst;
	while (curr_node && curr_node -> next)
		curr_node = curr_node -> next;
	curr_node -> next = new;
}

void	*ft_garbage_collector(void *ptr, bool clean)
{
	static t_list	*garbage_list;

	if (clean)
	{
		//ft_lstclear(&garbage_list, ft_del);
		return (NULL);
	}
	else
	{
		ft_lst_add_back(&garbage_list, ft_lst_new(ptr));
		return (ptr);
	}
}

void	ft_update(char *key, char *value, t_env *env, bool c)
{
	while (env)
	{
		if (!ft_strncmp(key, env->key, ft_strlen(key)))
		{
			if (value)
				env->value = ft_garbage_collector(ft_strdup(value), false);
			return ;
		}
		env = env->next;
	}
	if (c)
		ft_lstadd_back_env(&env, ft_lst_env_new(key, value));
}
