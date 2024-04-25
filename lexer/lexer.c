/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:01:37 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/25 17:56:36 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*static int	ft_token_join(t_token *src, t_token *add)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = malloc(sizeof (char *) * ft_len_tab(src->value) + ft_len_tab(add->value));
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
	tmp = token;
	while(tmp)
	{
		tmp2 = tmp;
		while (tmp2 && tmp2->next && tmp2->type != __pipe)
		{
			if (tmp2->type == __cmdgr && tmp != tmp2)
			{
				if (ft_token_join(tmp2, tmp))
					return (1);
				tmp2->prev->next = tmp2->next;
				tmp2->next->prev = tmp2->prev->next;
				tmp3 = tmp2;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
		if (tmp3)
			ft_free_token(tmp3);
	}
	return (0);
}*/

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
	ft_group_cmd(tokens);
	//{}// error*/
	return (tokens);
}
