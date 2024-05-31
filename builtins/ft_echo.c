/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:47:48 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/30 13:49:03 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*skip_dquotes(char *str)
{
	char	*str_clean;
	int		i;
	int		j;
	int		dquotes;

	i = 0;
	dquotes = 0;
	while (str[i])
	{
		if (str[i] == '"')
			dquotes++;
		i++;
	}
	if (dquotes % 2 != 0)
		return (NULL);
	i = -1;
	j = 0;
	str_clean = ft_calloc(sizeof(char), ft_strlen(str) - dquotes + 1);
	while (str[++i])
	{
		if (str[i] != '"')
			str_clean[j++] = str[i];
	}
	str_clean[j] = '\0';
	return (str_clean);
}

static char	*skip_squotes(char *str)
{
	char	*str_clean;
	int		i;
	int		j;
	int		squotes;

	i = 0;
	squotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			squotes++;
		i++;
	}
	if (squotes % 2 != 0)
		return (NULL);
	i = -1;
	j = 0;
	str_clean = ft_calloc(sizeof(char), ft_strlen(str) - squotes);
	while (str[++i])
	{
		if (str[i] != '\'')
			str_clean[j++] = str[i];
	}
	str_clean[j] = '\0';
	return (str_clean);
}

char	*clean_str(char *str)
{
	char	*str_clean;
	int		i;

	i = 0;
	str_clean = str;
	while (str[i])
	{
		if (str[i] == '"')
		{
			str_clean = skip_dquotes(str);
			break ;
		}
		if (str[i] == '\'')
		{
			str_clean = skip_squotes(str);
			break ;
		}
		i++;
	}
	return (str_clean);
}

static int	option_check(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **av)
{
	int		i;
	int		option;
	char	*str;

	i = 1;
	option = 0;
	while (av[i] != NULL && option_check(av[i]) == 1)
	{
		option = 1;
		i++;
	}
	while (av[i])
	{
		str = clean_str(av[i]);
		ft_putstr_fd(str, 1);
		if (av[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
