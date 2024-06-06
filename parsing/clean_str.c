/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:00:56 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/06 17:00:21 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*skip_again_simple(char *str, int squotes, int *i)
{
	int		j;
	char	*str_clean;

	j = 0;
	str_clean = ft_calloc(sizeof(char), ft_strlen(str) - squotes + 1);
	(*i)++;
	while (str[(*i)] && str[(*i)] != '\'')
		str_clean[j++] = str[(*i)++];
	str_clean[j] = '\0';
	if (str[(*i)])
		(*i)++;
	return (str_clean);
}

static char	*skip_squotes(char *str, int *i)
{
	char	*str_clean;
	int		d;
	int		squotes;

	squotes = 0;
	d = 0;
	while (str[d])
	{
		if (str[d] == '\'')
			squotes++;
		d++;
	}
	if (squotes % 2 != 0)
	{
		ft_putstr_fd("Symtax error, quote unclosed\n", 2);
		exit(0);
	}
	str_clean = skip_again_simple(str, squotes, i);
	return (str_clean);
}

static char	*no_quotes(char *str, int *i)
{
	char	*str_clean;
	int		j;

	j = 0;
	str_clean = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	while (str[(*i)])
	{
		if (str[(*i)] == '\'' || str[(*i)] == '"')
			break ;
		str_clean[j] = str[(*i)];
		(*i)++;
		j++;
	}
	str_clean[j] = '\0';
	if (str[(*i)])
		(*i)++;
	return (str_clean);
}

char	*clean_str(char *str)
{
	char	*str_clean;
	int		i;

	i = 0;
	str_clean = NULL;
	while (str[i])
	{
		if (str[i] == '"')
			str_clean = ft_strjoin(str_clean, skip_dquotes(str, &i), true);
		else if (str[i] == '\'')
			str_clean = ft_strjoin(str_clean, skip_squotes(str, &i), true);
		else
			str_clean = ft_strjoin(str_clean, no_quotes(str, &i), true);
	}
	return (str_clean);
}
