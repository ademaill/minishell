/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:14:24 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/29 13:33:20 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_ut(char *str, t_env *env)
{
	t_env	*prev;

	prev = NULL;
	if (!env)
		return ;
	while (env)
	{
		if (!ft_strncmp(str, env->key, ft_strlen(str)))
		{
			if (prev)
				prev->next = env->next;
			free(env);
		}
		prev = env;
		env = env->next;
	}
}

int	ft_unset(char **av, t_env *env)
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
			unset_ut(av[i], env);
		i++;
	}
	return (0);
}
