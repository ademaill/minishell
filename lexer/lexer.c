/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:01:37 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/03 17:07:40 by ademaill         ###   ########.fr       */
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
		add->value[j] = NULL;
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
	t_token *token;
	t_token *tmp;
	int		i;

	token = main->token;
	i = 2;
	while (token)
	{
		if (token->type == __cmdgr && token->next)
		{
			tmp = token->next;
			while (tmp)
			{
				if (tmp->type != __pipe && tmp->type != __cmdgr)
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

char	**creat_tab(char **src)
{
	int		i;
	int		j;
	char	**dest;

	i = 0;
	j = 2;
	dest = ft_calloc(sizeof (char *), ft_len_tab(src) - j + 2);
	if (!dest)
		return (NULL);
	while (src[j])
	{
		dest[i] = src[j];
		src[j] = NULL;
		j++;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

t_token	*ft_tokenizer(char *line, t_main *main)
{
	int		i;
	char	**content;
	char	**tab;
	char	*str;

	i = 0;
	str = NULL;
	tab = ft_split_ms(line, "<>|");
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "<<", 2) != 0)
			str = ft_cmd_pre_expand(tab[i], main);
		else
			str = tab[i];
		content = ft_split_ms(str, " ");
		if (content && content[0] != NULL)
			ft_new_node(&main->token, content);
		i++;
	}
	ft_cmd_type(main);
	ft_sort(main);
//	clear_token(main);
	return (main->token);
}
