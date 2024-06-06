/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:47:48 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/06 16:35:27 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static unsigned long	option_check(char *str)
{
	unsigned long	i;

	i = 0;
	if (str[0] != '-')
		return (0);
	while (str[i] == '-')
		i++;
	if (i == ft_strlen(str))
		return (0);
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
		free(str);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
