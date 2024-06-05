/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:14:24 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/04 16:54:58 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_ut(char *str, t_main *main)
{
	t_env	*prev;

	prev = NULL;
	if (!main->env)
		return ;
	while (main->env)
	{
		if (!ft_strncmp(str, main->env->key, ft_strlen(str)))
		{
			if (prev)
				prev->next = main->env->next;
			free(main->env);
		}
		prev = main->env;
		main->env = main->env->next;
	}
}

int	ft_unset(char **av, t_main *main)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!check_key(av[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(av[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
			unset_ut(av[i], main);
		i++;
	}
	return (0);
}
