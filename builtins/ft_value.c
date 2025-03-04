/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_value.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:14:51 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/13 14:10:26 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*value_condition(char *str, int *i, int *j, char *value)
{
	if (str[(*i)] == '=' && str[(*i) + 1] != '\'')
	{
		value = ft_calloc(sizeof(char), (ft_strlen(str) - (*i)));
		(*i)++;
		while (str[(*i)] != '\0')
			value[(*j)++] = str[(*i)++];
	}
	else if (str[(*i)] == '=' && str[(*i) + 1] == '\'')
	{
		value = ft_calloc(sizeof(char), (ft_strlen(str) - (*i)));
		(*i)++;
		while (str[(*i)] != '\0')
			value[(*j)++] = str[(*i)++];
	}
	return (value);
}

char	*ft_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	value = NULL;
	while (str[i++])
	{
		value = value_condition(str, &i, &j, value);
		if (str[i] == '\0')
		{
			if (!value)
				return (NULL);
			break ;
		}
	}
	value[j] = '\0';
	return (value);
}
