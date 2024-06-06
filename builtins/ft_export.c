/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:14:47 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/06 13:25:32 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_export_error(char *identifier)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

bool	ft_env_exists(char *key, t_main *main)
{
	t_env	*env;

	env = main->env;
	while (env)
	{
		if (ft_strncmp(key, env->key, ft_strlen(key)) == 0)
			return (true);
		env = env->next;
	}
	return (false);
}
//pas sur du void

static void	export_condition(char **av, int *i, t_main *main)
{
	char	*key;
	t_env	*env;
	t_env	*head;

	env = main->env;
	head = main->env;
	key = ft_key(av[(*i)]);
	if (ft_env_exists(key, main))
	{
		while (env)
		{
			if (ft_strncmp(key, env->key, ft_strlen(key)) == 0)
			{
				if (find_char(av[(*i)], '=') == 1)
					env->value = ft_value(av[(*i)]);
				break ;
			}
			env = env->next;
		}
	}
	else
		ft_lstadd_back_env(&env, ft_lst_env_new(key, ft_value(av[(*i)])));
	main->env = head;
}

int	ft_export(char **av, t_main *main)
{
	int		i;
	int		error_s;

	i = 1;
	error_s = 0;
	if (!av[1])
	{
		ft_export_list(main);
		return (0);
	}
	while (av[i])
	{
		if (check_key(av[i]) == 0)
			error_s = ft_export_error(av[i]);
		else
			export_condition(av, &i, main);
		i++;
	}
	return (error_s);
}
