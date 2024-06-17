/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:41:02 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/13 17:07:05 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	condition_lst(t_env *list)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = clean_str(list->value);
	printf("declare -x %s=\"", list->key);
	i = 0;
	while (tmp && tmp[i])
	{
		if (tmp[i] == '$' || tmp[i] == '"')
			printf("\\%c", tmp[i++]);
		else
			printf("%c", tmp[i++]);
	}
	free (tmp);
	printf("\"\n");
}

void	ft_export_list(t_main *main)
{
	t_env	*list;
	int		k_s;

	list = main->env;
	sort_lst(&list);
	while (list)
	{
		k_s = ft_strlen(list->key);
		if (list->value != NULL && (ft_strncmp(list->key, "_", k_s) != 0))
		{
			if (!list->value)
				printf("declare -x %s\"", list->key);
			else
				condition_lst(list);
		}
		else if (list->value == NULL && (ft_strncmp(list->key, "_", k_s) != 0))
			printf("declare -x %s\n", list->key);
		list = list->next;
	}
}

static int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	export_next(char *key, char **av, int *i, t_env *env)
{
	free(key);
	if (find_char(av[(*i)], '=') == 1)
		free(env->value);
	if (find_char(av[(*i)], '=') == 1)
		env->value = ft_value(av[(*i)]);
}
