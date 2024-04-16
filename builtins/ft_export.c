/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:14:47 by vnavarre          #+#    #+#             */
/*   Updated: 2024/04/02 11:36:45 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_name(char *name)
{
	int	i;

	i = 0;
		while (name[i])
	{
		if (!ft_isalnum((int)name[i]) && name[i] != '_')
		{
			ft_putstr_fd("Invalid name\n", 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export(char **av)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	if (!av[1] || !ft_strrchr(av[1], (int)'='))
		return (1);
	while (av[1][i] && av[1][i] != '=')
		i++;
	name = ft_substr(av[1], 0, i);
	if (check_name(name))
	{
		free(name);
		return (1);
	}
	i++;
	value = ft_strdup(av[1] + i);
	// fonction pour l'env.
	free(name);
	free(value);
	return(0);
}
