/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:14:24 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/16 15:37:07 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_ut(char *str, char **envp)
{
	t_env	*prev;
	t_env	*act;

	prev = NULL;
	act = ft_env_int(envp);
	if (!act)
		return ;
	while (act)
	{
		if (!ft_strncmp(str, act->key, ft_strlen(str)))
		{
			if (prev)
				prev->next = act->next;
			free(act);
		}
		prev = act;
		act = act->next;
	}
}

int	ft_unset(char **av, char **envp)
{
	int	i;

	i = 1;
	if (!av[1])
		return (0);
	while (av[i])
	{
		if (!check_key(av[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(av[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
			unset_ut(av[i], envp);
		i++;
	}
	return (1);
}
