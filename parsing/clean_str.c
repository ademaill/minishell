/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:00:56 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/04 13:45:38 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*skip_dquotes(char *str, int *i)
{
	char	*str_clean;
	int		j;
	int		d;
	int		dquotes;

	dquotes = 0;
	d = 0;
	while (str[d])
	{
		if (str[d] == '"')
			dquotes++;
		d++;
	}
	if (dquotes % 2 != 0)
	{
		ft_putstr_fd("Symtax error, quote unclosed\n", 2);
		exit(0);
	}
	j = 0;
	str_clean = ft_calloc(sizeof(char), ft_strlen(str) - dquotes + 1);
	(*i)++;
	while (str[(*i)] && str[(*i)] != '"')
	{
			str_clean[j++] = str[(*i)++];
	}
	str_clean[j] = '\0';
	if (str[(*i)])
		(*i)++;
	return (str_clean);
}

static char	*skip_squotes(char *str, int *i)
{
	char	*str_clean;
	int		j;
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
	j = 0;
	str_clean = ft_calloc(sizeof(char), ft_strlen(str) - squotes + 1);
	(*i)++;
	while (str[(*i)] && str[(*i)] != '\'')
	{
			str_clean[j++] = str[(*i)++];
	}
	str_clean[j] = '\0';
	if (str[(*i)])
		(*i)++;
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
		{
			str_clean = ft_strjoin(str_clean, skip_dquotes(str, &i));
			//break ;
		}
		else if (str[i] == '\'')
		{
			str_clean = ft_strjoin(str_clean, skip_squotes(str, &i));
			//break ;
		}
		else
		{
			str_clean = ft_strjoin(str_clean, no_quotes(str, &i));
		}
	}
	return (str_clean);
}
