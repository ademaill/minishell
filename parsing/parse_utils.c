/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:36:12 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/22 14:45:21 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	str_modify(t_token *token)
{
	char	*str;
	char	*tmp;
	int		i;

	tmp = ft_calloc(sizeof(char ), ft_strlen(token->value[0]));
	token->value[1] = ft_calloc(sizeof(char *), 1);
	i = 1;
	str = token->value[0];
	while (str[i])
	{
		tmp[i - 1] = str[i];
		i++;
	}
	token->value[0][0] = str[0];
	token->value[0][1] = '\0';
	i = 0;
	while (tmp[i])
	{
		token->value[1][i] = tmp[i];
		i++;
	}
	token->value[1][i] = '\0';
	token->value[2] = NULL;
}

void	str_modify2(t_token *token)
{
	char	*str;
	char	*tmp;
	int		i;

	tmp = ft_calloc(sizeof(char ), ft_strlen(token->value[0]));
	token->value[1] = ft_calloc(sizeof(char *), 1);
	i = 2;
	str = token->value[0];
	while (str[i])
	{
		tmp[i - 2] = str[i];
		i++;
	}
	token->value[0][0] = str[0];
	token->value[0][1] = str[1];
	token->value[0][2] = '\0';
	i = 0;
	while (tmp[i])
	{
		token->value[1][i] = tmp[i];
		i++;
	}
	token->value[1][i] = '\0';
	token->value[2] = NULL;
	free(tmp);
}

void	error_parse(char *str, t_token *token)
{
	t_token	*tmp;
	int	i;

	token = ft_lstfirst(token);
	while (token)
	{
		tmp = token->next;
		i = 0;
		while (token->value[i])
		{
			free(token->value[i]);
			i++;
		}
		free(token->value);
		free(token);
		token = tmp;
	}
	free (token);
	ft_putstr_fd("Error synthax,\n", 2);
	ft_putstr_fd(str, 2);
	minishell_loop();
}
