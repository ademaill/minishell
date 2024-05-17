/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:47:48 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/17 14:39:11 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*clean_str(char *str)
{
	int		i;
	char	*str_clean;
	int		j;

	i = 0;
	j = 0;
	str_clean = malloc(sizeof(char) * ft_strlen(str) - 1);
	if (!str)
		return (NULL);
	if (str[i] == '"' || str[i] == '\'')
		i++;
	while (str[i] && (str[i] != '"' && str[i] != '\''))
	{
		str_clean[j] = str[i];
		i++;
		j++;
	}
	str_clean[j] = '\0';
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

void	ft_echo(char **av)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	while (av[i] != NULL && option_check(av[i]) == 1)
	{
		option = 1;
		i++;
	}
	while (av[i])
	{
		ft_putstr_fd(clean_str(av[i]), 1);
		if (av[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
}
