/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:36:44 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/06 20:26:29 by vnavarre         ###   ########.fr       */
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

static void	exit_and_free(char *str, t_main *main)
{
	ft_putstr_fd(" numeric argument required\n", 2);
	free(str);
	if (main)
		free_all(main);
	exit(2);
}

static int	check_exit(char *str, int size, t_main *main)
{
	bool	error;
	int		code;

	code = 0;
	error = false;
	if (str)
		code = ft_exitatoi(str, &error);
	if (error)
		exit_and_free(str, main);
	if (size > 2)
	{
		ft_putstr_fd(" too many arguments\n", 2);
		return (1);
	}
	if (str)
		free(str);
	if (code)
	{
		free_all(main);
		exit(code);
	}
	code = main->exit_code;
	free_all(main);
	exit(code);
	return (0);
}

int	ft_exit(t_main *main, char **value)
{
	int		i;
	char	*str;
	int		size;

	i = 0;
	str = NULL;
	size = ft_len_tab(value);
	close(main->original_stdin);
	close(main->here_doc_stdin);
	if (value[1])
		str = clean_str(value[1]);
	if (!str && size == 2)
		exit_and_free(str, main);
	if (str && (str[i] == '-' || str[i] == '+'))
		i++;
	if (str)
	{
		while (str[i])
		{
			if (ft_isdigit(str[i]) != 1)
				exit_and_free(str, main);
			i++;
		}
	}
	check_exit(str, size, main);
	return (1);
}
