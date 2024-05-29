/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:36:44 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/29 13:20:42 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

static int	ft_isspace(const char a)
{
	if (a == ' ' || (a >= '\t' && a <= '\r'))
		return (1);
	return (0);
}

static __int128_t	ft_exitatoi(const char *nptr, bool *error)
{
	int			i;
	int			pos;
	__int128_t	result;

	i = 0;
	pos = 1;
	result = 0;
	while (ft_isspace(nptr[i]) == 1)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			pos = pos * (-1);
		i++;
	}
	while (ft_isdigit(nptr[i]) == 1)
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	result = result * pos;
	if (result < LLONG_MIN || result > LLONG_MAX)
		*error = true;
	return (result);
}

int	ft_exit(t_main *main, char **value)
{
	int		code;
	bool	error;
	int		i;
	char	*str;
	int		size;

	code = 0;
	i = 0;
	error = false;
	str = NULL;
	(void)main;
	size = ft_len_tab(value);
	if (size == 2)
	{
		str = clean_str(value[1]);
		if(!str)
		{
				ft_putstr_fd(" numeric argument required", 2);
				exit(2);
		}
		if (str[i] == '-' || str[i] == '+')
			i++;
		while (str[i])
		{
			if (ft_isdigit(str[i]) != 1)
			{
				ft_putstr_fd(" numeric argument required", 2);
				exit(2);
			}
			i++;
		}
		code = ft_exitatoi(str, &error);
		if (error)
		{
			ft_putstr_fd(" numeric argument required", 2);
			exit(2);
		}
		exit(code);
	}
	else if (size > 2)
	{
		ft_putstr_fd(" too many arguments", 2);
		return (1);
	}
	exit(0);
}
