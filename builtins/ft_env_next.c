/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:39:13 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/03 17:42:56 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_check_value(char *str, int *i, int *j, char *value)
{
	if (str[(*i)] == '=')
	{
		value = malloc(sizeof(char) * (ft_strlen(str) - (*i)));
		if (!value)
			return (NULL);
		(*i)++;
		if (str[(*i)] == '"')
			(*i)++;
		while (str[(*i)] != '\0')
		{
			value[(*j)++] = str[(*i)++];
			if (str[(*i)] == '"')
				break ;
		}
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
		value = ft_check_value(str, &i, &j, value);
		if (str[i] == '\0')
		{
			if (!value)
				value = malloc(sizeof(char) + 1);
			break ;
		}
	}
	value[j] = '\0';
	return (value);
}
