/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:01:37 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/18 16:47:03 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	token_type(t_token *token)
{
	if (token->value[0][0] == '|')
		parse_pipe(token);
	else if (token->value[0][0] == '<' && token->value[0][1] == '<')
		parse_here_doc(token);
	else if (token->value[0][0] == '>' && token->value[0][1] == '>')
		parse_append(token);
	else if (token->value[0][0] == '>' || token->value[0][0] == '<')
		parse_redirect(token);
	else if (token->value[0][0] == '$')
		token->type = __var_env;
	else
		token->type = __cmdgr;
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

t_token	*ft_tokenizer(char *line)
{
	int		i;
	char	**content;
	t_token	*tokens;
	char	**tab;
	t_token *tmp;

	tokens = NULL;
	i = 0;
	tab = ft_split_ms(line, "<>|");
	while (tab[i])
	{
		content = ft_split_ms(tab[i], " ");
		ft_new_node(&tokens, content);
		i++;
	}
	free_tab(tab);
	tmp = tokens;
	while (tmp)
	{
		token_type(tmp);
		tmp = tmp->next;
	}
	return (tokens);
}
