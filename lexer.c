/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:01:37 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/12 14:01:44 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	token_type(t_token *token)
{
	if (token->value[0][0] == '|')
		token->type = __pipe;
	else if (token->value[0][0] == '<' && token->value[0][1] == '<')
		token->type = __here_doc;
	else if (token->value[0][0] == '>' && token->value[0][1] == '>')
		token->type = __append;
	else if (token->value[0][0] == '>' || token->value[0][0] == '<')
		token->type = __redirect;
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

	tokens = (t_token *)malloc(sizeof (t_token));
	tokens = NULL;
	i = 0;
	tab = ft_split_ms(line, "<>|");
	while (tab[i])
	{
		content = ft_split_ms(tab[i], " ");
		ft_lstadd_back(&tokens, ft_lstnew(content));
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

#include <stdio.h>

int	main(int argc, char **arg)
{
	(void) argc;
	(void) arg;
	//char *str;
	t_token *arr;
	int	i;
	//str = arg[1];
	i = 0;
	arr = ft_tokenizer("$fnrjksf");
	while (arr)
	{
		printf("token numero %d\n", i);
		i++;
		printf("%s\n", arr->value[0]);
		if (arr->value[1])
			printf("%s\n", arr->value[1]);
		if (arr->type == 0)
			printf("type : _cmdgrp\n\n");
		else if (arr->type == 1)
			printf("type : _pipe\n\n");
		else if (arr->type == 2)
			printf("type : _redirect\n\n");
		else if (arr->type == 3)
			printf("type : _var_env\n\n");
		else if (arr->type == 4)
			printf("type : _here_doc\n\n");
		else if (arr->type == 5)
			printf("type : _append\n\n");
		arr = arr->next;
	}
	return (0);
}
