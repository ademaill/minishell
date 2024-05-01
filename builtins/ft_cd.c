/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:20:37 by vnavarre          #+#    #+#             */
/*   Updated: 2024/04/27 16:43:01 by vnavarre         ###   ########.fr       */
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
	ft_putstr_fd("minishell: cd: `", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
	return (1);
}

int	ft_cd(char *path, char **envp)
{
	t_env	*env;

	env = ft_env_int(envp);
	if (!path)
		return (get_home(env));
	if (chdir(path) != 0)
		return (ft_cd_error(path));
	ft_update("OLDPWD", ft_get_envlst_val("PWD", env), env, false);
	ft_change_pwd(env);
	printf("%s\n", ft_get_envlst_val("PWD", env));
	printf("%s\n", ft_get_envlst_val("OLDPWD", env));
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	ft_cd(av[1], envp);
	return (0);
}
