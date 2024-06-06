/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:36:27 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/05 19:19:42 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_key(char *str)
{
	size_t	i;
	char	*key;

	i = 0;
	key = NULL;
	while (str[i])
	{
		if (str[i] == '=' || str[i + 1] == '\0')
		{
			key = malloc(sizeof(char) * i + 1);
			if (!key)
				return (NULL);
			i = 0;
			while (str[i] != '=' && str[i] != '\0')
			{
				key[i] = str[i];
				i++;
			}
			key[i] = '\0';
		}
		if (str[i] == '=' || str[i] == '\0')
			break ;
		i++;
	}
	return (key);
}

t_env	*ft_lst_env_new(char *key, char *value)
{
	t_env	*elmt;

	elmt = (t_env *)malloc(sizeof(*elmt));
	if (!elmt)
		return (NULL);
	elmt->key = key;
	elmt->value = value;
	elmt->next = NULL;
	return (elmt);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*list;

	if (!new)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	list = (*lst);
	while (list->next)
		list = list->next;
	list->next = new;
}

t_env	*ft_env_int(char **envp)
{
	int		i;
	t_env	*lst;
	char	*key;
	char	*value;
	char	**env;

	i = 0;
	env = envp;
	lst = NULL;
	if (!env)
		return (0);
	while (env[i])
	{
		key = ft_key(env[i]);
		value = ft_value(env[i]);
		ft_lstadd_back_env(&lst, ft_lst_env_new(key, value));
		i++;
	}
	return (lst);
}

void	ft_env(t_env *env)
{
	t_env	*list;

	list = env;
	while (list)
	{
		if (list->value != NULL)
			printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
}
