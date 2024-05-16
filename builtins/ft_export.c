/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:14:47 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/16 12:58:13 by vnavarre         ###   ########.fr       */
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

static	void	ft_export_list(t_main *main)
{
	t_env	*list;
	int		i;
	int		k_s;

	list = main->env;
	while (list)
	{
		k_s = ft_strlen(list->key);
		if (list->value != NULL && (ft_strncmp(list->key, "_", k_s) != 0))
		{
			if (!list->value)
				printf("declare -x %s\"", list->key);
			else
			{
				printf("declare -x %s=\"", list->key);
				i = 0;
				while (list->value[i])
				{
					if (list->value[i] == '$' || list->value[i] == '"')
						printf("\\%c", list->value[i++]);
					else
						printf("%c", list->value[i++]);
				}
				printf("\"\n");
			}
		}
		else if (list->value == NULL && (ft_strncmp(list->key, "_", k_s) != 0))
			printf("declare -x %s\n", list->key);
		list = list->next;
	}
}

int	ft_export(char **av, t_main *main)
{
	char	*key;
	int		i;
	int		error_s;
	t_env	*env;
	t_env	*head;

	i = 1;
	error_s = 0;
	env = main->env;
	head = main->env;
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
		{
			key = ft_key(av[i]);
			if (ft_env_exists(key, main))
			{
				while (env)
				{
					if (ft_strncmp(key, env->key, ft_strlen(key)) == 0)
					{
						printf("%s\n", env->key);
						env->value = ft_value(av[i]);
						break ;
					}
					env = env->next;
				}
			}
			else
				ft_lstadd_back_env(&env, ft_lst_env_new(key, ft_value(av[i])));
			main->env = head;
		}
		i++;
	}
	/*while (env)
	{
		if (env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}*/
	return (error_s);
}
