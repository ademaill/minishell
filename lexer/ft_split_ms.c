/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:38:21 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/13 16:37:27 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	quotes_jump(char *str)
{
	int		i;
	char	c;

	if (!str)
		return (0);
	if ((str && str[0] != '\'' && str[0] != '"')
		|| !ft_strchr(&str[1], str[0]))
		return (0);
	c = str[0];
	i = 1;
	while (str[i] && str[i] != c)
		++i;
	return (i);
}

static int	ft_count_words(char *str, char *sep)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	if (!str)
		return (0);
	while (str && str[i])
	{
		i += quotes_jump(&str[i]);
		if (str[i] && ft_strchr(sep, str[i])
			&& str[i] == str[i + 1] && str[i] == '|')
		{
			++i;
			count += 2;
		}
		else if (ft_strchr(sep, str[i]))
			++count;
		else if (i == 0 || ft_strchr(sep, str[i - 1]))
			++count;
		if (str[i])
			++i;
	}
	return (count + 1);
}

static int	get_next_sep(char *str, char *sep)
{
	int	i;

	i = 0;
	if (str[i] && ft_strchr(sep, str[i]))
	{
		if (str[++i] == str[0])
			++i;
		if (str[0] == '<' || str[0] == '>')
		{
			while (str[i] == ' ' || str[i] == '	')
				++i;
			while (str[i] && !ft_strchr(" <|>", str[i]))
				i += quotes_jump(&str[i]) + 1;
		}
		return (i);
	}
	if (sep[0] == ' ' && (str[0] == '<' || str[0] == '>'))
	{
		while (str[i] == str[0])
			i++;
		return (i);
	}
	while (!ft_strchr(sep, str[i]))
		i += quotes_jump(&str[i]) + 1;
	return (i);
}

char	**ft_split_ms(char *str, char *sep)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	tab = NULL;
	if (str && str[0])
		tab = ft_calloc(sizeof(char *), ft_count_words(str, sep));
	if (str && str[0] && !tab)
		return (NULL);
	i = 0;
	k = -1;
	while (str && str[0] && str[i] && (i == 0 || str[i - 1]))
	{
		if ((str[i] == ' ' || str[i] == '	') && ++i)
			continue ;
		j = get_next_sep(&str[i], sep);
		tab[++k] = ft_strndup(&str[i], j);
		if (!tab[k])
			return (NULL);
		i += j;
	}
	if (str)
		free(str);
	return (tab);
}
