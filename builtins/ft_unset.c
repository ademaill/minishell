/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:14:24 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/17 09:08:57 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_ut(char *str, t_main *main)
{
	t_env	*prev;
	t_env	*env;

	prev = NULL;
	env = main->env;
	if (!env)
		return ;
	while (env)
	{
		if (!ft_strncmp(str, env->key, ft_strlen(str)))
		{
			if (!prev)
				main->env = env->next;
			if (prev)
				prev->next = env->next;
			free(env->key);
			free(env->value);
			free(env);
			break ;
		}
		prev = env;
		env = env->next;
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
