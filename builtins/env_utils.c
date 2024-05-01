/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:23:47 by vnavarre          #+#    #+#             */
/*   Updated: 2024/04/27 16:34:39 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

char	*ft_get_envlst_val(char *key, t_env *envlst)
{
	while (envlst)
	{
		if (!ft_strncmp(key, envlst->key, ft_strlen(key)))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

int	check_key(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	sort_lst(t_env **head)
{
	t_env	*sorted;
	t_env	*cur;
	t_env	*next;
	t_env	*tmp;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	sorted = NULL;
	cur = *head;
	while (cur != NULL)
	{
		next = cur->next;
		if (sorted == NULL || ft_strcmp(sorted->key, cur->key) >= 0)
		{
			cur->next = sorted;
			sorted = cur;
		}
		else
		{
			tmp = sorted;
			while (tmp->next != NULL && ft_strcmp(tmp->next->key, cur->key) < 0)
				tmp = tmp->next;
			cur->next = tmp->next;
			tmp->next = cur;
		}
		cur = next;
	}
	*head = sorted;
}
