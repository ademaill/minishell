/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:20:37 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/13 13:41:38 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_change_oldpwd(t_env *env)
{
	t_env	*old;
	t_env	*curr;

	old = ft_get_envlst("OLDPWD", env);
	curr = ft_get_envlst("PWD", env);
	if (old && curr)
	{
		free(old->value);
		old->value = curr->value;
		return (0);
	}
	return (1);
}

static int	ft_change_pwd(t_env *env)
{
	char	*cwd;
	t_env	*curr;

	cwd = getcwd(NULL, 0);
	curr = ft_get_envlst("PWD", env);
	if (cwd && curr)
	{
		curr->value = cwd;
		return (0);
	}
	free(cwd);
	return (1);
}

static int	get_home(t_env *env)
{
	t_env	*home;
	t_env	*curr;

	home = ft_get_envlst("HOME", env);
	curr = ft_get_envlst("PWD", env);
	if (home && curr)
	{
		ft_change_oldpwd(env);
		curr->value = ft_strdup(home->value);
		chdir(home->value);
		return (0);
	}
	else
	{
		ft_putstr_fd("Home not set\n", 2);
		return (1);
	}
	return (1);
}

static int	ft_cd_error(char *err_msg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(err_msg, 2);
	if (open(err_msg, O_RDONLY) > 0)
		ft_putstr_fd(": Not a Directory\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

int	ft_cd(char **path, t_main *main)
{
	t_env	*env;

	env = main->env;
	if (path[2])
	{
		ft_putstr_fd(" too many arguments\n", 2);
		return (1);
	}
	if (!path[1])
		return (get_home(env));
	if (chdir(path[1]) != 0)
		return (ft_cd_error(path[1]));
	ft_change_oldpwd(env);
	ft_change_pwd(env);
	return (0);
}
