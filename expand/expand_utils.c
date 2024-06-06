/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:28:22 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/06 14:07:33 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_handle_str(char *str, int *i)
{
	int		start;
	char	*tmp;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$'
		&& str[*i] != '\0')
		(*i)++;
	tmp = ft_substr(str, start, *i - start);
	return (tmp);
}

char	*ft_handle_d_quotes(char *str, int *i, bool dquotes)
{
	int		start;
	char	*tmp;

	start = *i;
	if (!dquotes)
	{
		(*i)++;
		while (str[*i] != '"' && str[*i] != '\''
			&& str[*i] != '$' && str[*i] != '\0')
			(*i)++;
	}
	else
	{
		(*i)++;
		while (str[*i] != '"' && str[*i] != '$' && str[*i] != '\0')
			(*i)++;
	}
	tmp = ft_substr(str, start, (*i - start));
	return (tmp);
}

char	*ft_handle_s_quotes(char *str, int *i, bool dquotes)
{
	int		start;
	char	*tmp;

	start = *i;
	if (!dquotes)
	{
		(*i)++;
		while (str[*i] != '\'' && str[*i] != '\0')
			(*i)++;
		(*i)++;
	}
	else
	{
		(*i)++;
		while (str[*i] != '\'' && str[*i] != '$' && str[*i] != '\0')
			(*i)++;
	}
	tmp = ft_substr(str, start, (*i - start));
	return (tmp);
}
