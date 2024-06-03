/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:01:40 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/03 16:22:25 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_export_list2(t_env *list, int k_s, int *i)
{
	if (list->value != NULL && (ft_strncmp(list->key, "_", k_s) != 0))
	{
		if (!list->value)
			printf("declare -x %s\"", list->key);
		else
		{
			printf("declare -x %s=\"", list->key);
			(*i) = 0;
			while (list->value[(*i)])
			{
				if (list->value[(*i)] == '$' || list->value[(*i)] == '"')
					printf("\\%c", list->value[(*i)++]);
				else
					printf("%c", list->value[(*i)++]);
			}
			printf("\"\n");
		}
	}
	else if (list->value == NULL && (ft_strncmp(list->key, "_", k_s) != 0))
		printf("declare -x %s\n", list->key);
}

void	ft_export_list(t_main *main)
{
	t_env	*list;
	int		i;
	int		k_s;

	list = main->env;
	while (list)
	{
		k_s = ft_strlen(list->key);
		ft_export_list2(list, k_s, &i);
		list = list->next;
	}
}
