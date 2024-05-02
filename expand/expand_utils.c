/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:28:22 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/01 16:33:13 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_handle_str(char *str, int *i)
{
	int		start;
	char	*tmp;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	tmp = ft_substr(str, start, *i - start);
	return (tmp);
}

char	*ft_handle_d_quotes(char *str, int *i)
{
	int		start;
	char	*tmp;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
		(*i)++;
	tmp = ft_substr(str, start, *i - start);
	return (tmp);
}

char	*ft_handle_s_quotes(char *str, int *i)
{
	int		start;
	char	*tmp;

	start = *i;
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	tmp = ft_substr(str, start, *i - start);
	return (tmp);
}
