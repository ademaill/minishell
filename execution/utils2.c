/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:01:11 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/06 17:56:30 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_builtins(t_token *token)
{
	if (!token)
		return (0);
	if (ft_strncmp(token->value[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "exit", 6) == 0)
		return (1);
	else
		return (0);
}

void	exec_builtins(t_token *token, t_main *main)
{
	if (ft_strncmp(token->value[0], "pwd", 4) == 0)
		main->exit_code = ft_pwd();
	else if (ft_strncmp(token->value[0], "cd", 3) == 0)
		main->exit_code = ft_cd(token->value, main);
	else if (ft_strncmp(token->value[0], "export", 7) == 0)
		main->exit_code = ft_export(token->value, main);
	else if (ft_strncmp(token->value[0], "echo", 5) == 0)
		main->exit_code = ft_echo(token->value);
	else if (ft_strncmp(token->value[0], "unset", 6) == 0)
		main->exit_code = ft_unset(token->value, main);
	else if (ft_strncmp(token->value[0], "env", 4) == 0)
		ft_env(main->env);
	else if (ft_strncmp(token->value[0], "exit", 5) == 0)
	{
		printf("exit\n");
		main->exit_code = ft_exit(main, token->value);
	}
}

static void	exec_else(char **cmd, char **envp)
{
	char	*path;
	char	*tmp;

	tmp = NULL;
	path = f_path(cmd[0], envp);
	if (!path)
	{
		tmp = ft_strdup(cmd[0]);
		free_tab(cmd);
		ft_error(tmp, 127, " command not found\n");
	}
	if (execve(path, cmd, envp) == -1)
	{
		tmp = cmd[0];
		free(path);
		ft_error(tmp, EXIT_FAILURE, " command not found\n");
	}
}

void	exec_cmd(char **cmd, char **envp, t_main *main)
{
	char	*tmp;
	DIR		*directory;

	tmp = NULL;
	if (!ft_env_exists("PATH", main))
		ft_error(cmd[0], 127, " command not found\n");
	if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
	{
		directory = opendir(cmd[0]);
		if (directory != NULL)
			ft_error(cmd[0], 126, " Is a directory\n");
		if (access(cmd[0], F_OK) != 0)
			ft_error(cmd[0], 127, " No such file or directory\n");
		if (access(cmd[0], R_OK) != 0)
			ft_error(cmd[0], 126, " Permission denied\n");
		if (execve(cmd[0], cmd, envp) != 0)
			ft_error(cmd[0], 126, " command not found\n");
	}
	else
		exec_else(cmd, envp);
}
