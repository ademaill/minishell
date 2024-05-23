/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:01:37 by ademaill          #+#    #+#             */
/*   Updated: 2024/05/23 14:24:37 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer.h"

int	ft_token_join(t_token *src, t_token *add, int j)
{
	char	**tab;
	int		i;

	i = 0;
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
		add->value[j] = NULL;
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

char	*ft_sort(char **tab, int i)
{
	int	j;
	char	*str;
	bool	first_is_cmd;
	bool	first_is_special;

	str = NULL;
	j = 0;
	first_is_cmd = false;
	first_is_special = false;
	while (tab[i + j])
	{
		if (ft_strncmp(tab[i + j], "|", 1) == 0)
			break;
		if ((ft_strncmp(tab[i + j], ">" ,1) == 0 || ft_strncmp(tab[i + j], "<" ,1) == 0 || ft_strncmp(tab[i + j], ">>" ,2) == 0 || ft_strncmp(tab[i + j], "<<" ,2) == 0) && !first_is_cmd)
		{
			if (j == 0)
				first_is_special = true;
			if (tab[i + 1])
			{
				str = ft_strjoin(ft_strjoin(tab[i], " "), tab[i + 1]);
				return (str);
			}
		}
		else
		{
			if (j == 0)
				first_is_cmd = true;
			str = ft_strjoin(str, tab[i + j]);
		}
		j++;
	}
	return (str);
}

t_token	*ft_tokenizer(char *line, t_main *main)
{
	int		i;
	char	**content;
	char	**tab;
	t_token	*tmp;
	char	*str;

	i = 0;
	tab = ft_split_ms(line, "<>|");
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "<<", 2) != 0)
			tab[i] = ft_cmd_pre_expand(tab[i], main);
		str = ft_sort(tab, i);
		content = ft_split_ms(str, " ");
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
	//ft_sort(main);
	return (main->token);
}
