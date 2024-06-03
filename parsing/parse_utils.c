/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:36:12 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/03 17:13:29 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void	str_modify(t_token *token)
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
}*/
void	str_modify(t_token *token)
{
	char	**tab;
	int		i;
	int		j;
	int		size;

	i = 0;
	size = ft_len_tab(token->value);
	tab = ft_calloc(sizeof(char *), size + 2);
	tab[0] = ft_calloc(sizeof(char), 2);
	tab[0][0] = token->value[0][0];
	tab[1] = ft_calloc(sizeof(char), ft_strlen(token->value[0]));
	while(token->value[0][i] && token->value[0][i + 1])
	{
		tab[1][i] = token->value[0][i + 1];
		i++;
	}
	i = 1;
	j = 2;
	while (i < size)
	{
		tab[j] = ft_strdup(token->value[i]);
		i++;
		j++;
	}
	token->value = tab;
}


void	str_modify2(t_token *token)
{
	char	**tab;
	int		i;
	int		j;
	int		size;

	i = 0;
	size = ft_len_tab(token->value);
	tab = ft_calloc(sizeof(char *), size + 2);
	tab[0] = ft_calloc(sizeof(char), 2);
	tab[0][0] = token->value[0][0];
	tab[0][1] = token->value[0][1];
	tab[1] = ft_calloc(sizeof(char), ft_strlen(token->value[0]));
	while(token->value[0][i] && token->value[0][i + 1])
	{
		tab[1][i] = token->value[0][i + 2];
		i++;
	}
	i = 1;
	j = 2;
	while (i < size)
	{
		tab[j++] = ft_strdup(token->value[i]);
		i++;
	}
	token->value = tab;
}

void	error_parse(char *str, t_token *token, t_main *main)
{
	t_token	*tmp;
	int		i;

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
	main->exit_code = 2;
	ft_putstr_fd("Error synthax,\n", 2);
	ft_putstr_fd(str, 2);
	minishell_loop(main);
}
