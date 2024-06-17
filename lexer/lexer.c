/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:01:37 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/13 18:28:19 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer.h"

int	ft_token_join(t_token *src, t_token *add, int j)
{
	char	**tab;
	int		i;
	int		size;

	i = 0;
	size = ft_len_tab(src->value) + ft_len_tab(add->value) - j + 1;
	tab = ft_calloc(sizeof (char *), size);
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

void	ft_sort(t_main *main)
{
	t_token	*token;
	t_token	*tmp;

	token = main->token;
	while (token)
	{
		if (token->type == __cmdgr && token->next)
		{
			tmp = token->next;
			while (tmp)
			{
				if (tmp->type != __pipe)
				{
					if (ft_len_tab(tmp->value) > 1)
						ft_token_join(token, tmp, 2);
				}
				if (tmp->type == __pipe)
					break ;
				tmp = tmp->next;
			}
		}
		token = token->next;
	}
}

static int	while_token(char **tab, t_main *main, char **content)
{
	int		i;
	char	*str;

	i = -1;
	while (tab[++i])
	{
		str = tab[i];
		if (ft_strncmp(tab[i], "<<", 2) != 0)
			str = ft_cmd_pre_expand(tab[i], main);
		content = ft_split_ms(str, " 	");
		if (!content)
			free_all(main);
		if (!content)
			return (1);
		if (content && !content[0])
		{
			free(content);
			content = NULL;
		}
		if (content && content[0] != NULL)
			ft_new_node(&main->token, content);
	}
	return (0);
}

t_token	*ft_tokenizer(char *line, t_main *main)
{
	char	**tab;

	tab = ft_split_ms(line, "<>|");
	if (!tab)
		return (NULL);
	if (while_token(tab, main, NULL) == 1)
	{
		free(tab);
		return (NULL);
	}
	free(tab);
	ft_cmd_type(main);
	ft_sort(main);
	go_regroup(main);
	return (main->token);
}
