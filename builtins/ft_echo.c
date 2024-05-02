/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:47:48 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/01 16:18:40 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	i = 0;
	option = 0;
	while (av[i] != NULL && option_check(av[i]) == 1)
	{
		option = 1;
		i++;
	}
	while (av[i])
	{
		ft_putstr_fd(av[i], 1);
		if (av[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
}

int	main(int ac, char **av)
{
	int		i;
	char	**ags;

	i = 0;
	ags = malloc((sizeof(char *) * ac));
	while (av[i] != NULL)
	{
		ags[i] = av[i + 1];
		i++;
	}
	ft_echo(ags);
	free(ags);
	return (0);
}
