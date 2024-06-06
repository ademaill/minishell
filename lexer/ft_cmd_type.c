/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:30:07 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/06 13:24:22 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../minishell.h"

static char	**creat_tab(char **src)
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

static void	while_cmd(t_token *tmp, int *count_cmdgr, t_main *main)
{
	t_token	*tmp2;

	tmp2 = tmp;
	while (tmp2)
	{
		token_type(tmp2, main);
		if (tmp2->type == __cmdgr)
			(*count_cmdgr)++;
		tmp2 = tmp2->next;
	}
	if ((*count_cmdgr) == 0 && ft_len_tab(tmp->value) > 2)
		ft_new_node(&main->token, creat_tab(tmp->value));
}

void	ft_cmd_type(t_main *main)
{
	t_token	*tmp;
	int		count_cmdgr;

	count_cmdgr = 0;
	tmp = main->token;
	while (tmp)
	{
		token_type(tmp, main);
		if (tmp->type == __pipe)
			count_cmdgr = 0;
		if (tmp->type == __cmdgr)
			count_cmdgr++;
		if (tmp->type == __redirect_in || tmp->type == __redirect_out
			|| tmp->type == __append || tmp->type == __here_doc)
			while_cmd(tmp, &count_cmdgr, main);
		tmp = tmp->next;
	}
}
