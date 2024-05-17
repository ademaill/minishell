/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:01:37 by ademaill          #+#    #+#             */
/*   Updated: 2024/05/17 14:17:07 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer.h"

int	ft_token_join(t_token *src, t_token *add)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = malloc(sizeof (char *) * (ft_len_tab(src->value) + ft_len_tab(add->value) + 1));
	if (!tab)
		return (1);
	while (src->value[i])
	{
		tab[i] = src->value[i];
		i++;
	}
	while (add->value[j])
	{
		tab[i] = add->value[j];
		i++;
		j++;
	}
	tab[i] = NULL;
	free(src->value);
	src->value = tab;
	return (0);
}

static int	ft_group_cmd(t_token *token)
{
	t_token	*tmp;
	t_token	*tmp2;
	t_token	*tmp3;

	tmp = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	if (!token)
		return (0);
	regroup(token, tmp, tmp2, tmp3);
	//if (regroup(token, tmp, tmp2, tmp3) == 1)
		//gestion d'erreur
	return (0);
}

void	token_type(t_token *token, t_main *main)
{
	if (token->value[0][0] == '|')
		parse_pipe(token, main);
	else if (token->value[0][0] == '<' && token->value[0][1] == '<')
		parse_here_doc(token, main);
	else if (token->value[0][0] == '>' && token->value[0][1] == '>')
		parse_append(token, main);
	else if (token->value[0][0] == '>' || token->value[0][0] == '<')
		parse_redirect(token, main);
	else
		token->type = __cmdgr;
}

t_token	*ft_tokenizer(char *line, t_main *main)
{
	int		i;
	char	**content;
	char	**tab;
	t_token	*tmp;

	i = 0;
	tab = ft_split_ms(line, "<>|");
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "<<", 2) != 0)
			tab[i] = ft_cmd_pre_expand(tab[i], main);
		content = ft_split_ms(tab[i], " ");
		if (content[0] != NULL)
			ft_new_node(&main->token, content);
		i++;
	}
	tmp = main->token;
	while (tmp)
	{
		token_type(tmp, main);
		tmp = tmp->next;
	}
	ft_group_cmd(main->token);
	return (main->token);
}
