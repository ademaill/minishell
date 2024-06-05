/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:20:37 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/04 15:56:13 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_change_pwd(t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_update("PWD", cwd, env, false);
	return (0);
}

static int	get_home(t_env *env)
{
	char	*home;

	ft_update("OLDPWD", ft_get_envlst_val("PWD", env), env, false);
	home = ft_get_envlst_val("HOME", env);
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home) == 0)
	{
		ft_update("PWD", home, env, false);
		return (0);
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
	ft_update("OLDPWD", ft_get_envlst_val("PWD", env), env, false);
	ft_change_pwd(env);
	return (0);
}
