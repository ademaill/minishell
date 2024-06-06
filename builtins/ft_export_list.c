/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:41:02 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/06 13:34:21 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	condition_lst(t_env *list)
{
	int	i;

	i = 0;
	printf("declare -x %s=\"", list->key);
	i = 0;
	while (list->value[i])
	{
		if (list->value[i] == '$' || list->value[i] == '"')
			printf("\\%c", list->value[i++]);
		else
			printf("%c", list->value[i++]);
	}
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
