/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:36:27 by vnavarre          #+#    #+#             */
/*   Updated: 2024/04/25 15:04:50 by vnavarre         ###   ########.fr       */
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
		if (str[i] == '=')
		{
			key = malloc(sizeof(char) * i);
			if (!key)
				return (NULL);
			i = 0;
			while (str[i] != '=')
			{
				key[i] = str[i];
				i++;
			}
		}
		if (str[i] == '=')
			break ;
		i++;
	}
	return (key);
}

char	*ft_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = -1;
	j = 0;
	value = NULL;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			value = malloc(sizeof(char) * (ft_strlen(str) - i));
			if (!value)
				return (NULL);
			i++;
			while (str[i] != '\0')
			{
				value[j++] = str[i];
				i++;
			}
		}
		if (str[i] == '\0')
			break ;
	}
	return (value);
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
	sort_lst(&lst);
	return (lst);
}

void	ft_env(char **envp)
{
	t_env	*list;

	list = ft_env_int(envp);
	while (list)
	{
		if (list->value != NULL)
			printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
}
