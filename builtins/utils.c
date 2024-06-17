/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:36:19 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/13 14:10:24 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

t_list	*ft_lst_new(void *content)
{
	t_list	*new_node;

	new_node = ft_calloc(1, sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lst_add_back(t_list **lst, t_list *new)
{
	t_list	*curr_node;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr_node = *lst;
	while (curr_node && curr_node->next)
		curr_node = curr_node->next;
	curr_node->next = new;
}

t_env	*ft_get_envlst(char *key, t_env *envlst)
{
	while (envlst)
	{
		if (!ft_strncmp(key, envlst->key, ft_strlen(key)))
			return (envlst);
		envlst = envlst->next;
	}
	return (NULL);
}

void	close_in_exit(t_main *main)
{
	close(main->original_stdin);
	close(main->here_doc_stdin);
}
