/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:01:11 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/03 17:22:37 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_builtins(t_token *token)
{
	if (!token)
		return (0);
	if (ft_strncmp(token->value[0], "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "export", 6) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "env", 3) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "exit", 5) == 0)
		return (1);
	else
		return (0);
}

void	exec_builtins(t_token *token, t_main *main)
{
	if (ft_strncmp(token->value[0], "pwd", 3) == 0)
		main->exit_code = ft_pwd();
	else if (ft_strncmp(token->value[0], "cd", 2) == 0)
		main->exit_code = ft_cd(token->value, main);
	else if (ft_strncmp(token->value[0], "export", 6) == 0)
		main->exit_code = ft_export(token->value, main);
	else if (ft_strncmp(token->value[0], "echo", 4) == 0)
		main->exit_code = ft_echo(token->value);
	else if (ft_strncmp(token->value[0], "unset", 5) == 0)
		main->exit_code = ft_unset(token->value, main->env);
	else if (ft_strncmp(token->value[0], "env", 3) == 0)
		ft_env(main->env);
	else if (ft_strncmp(token->value[0], "exit", 5) == 0)
	{
		printf("exit\n");
		main->exit_code = ft_exit(main, token->value);
	}
}

void	exec_cmd_error(void *directory, char **cmd, char **envp)
{
	if(directory != NULL)
		ft_error(cmd[0], 126, " Is a directory\n");
	if (access(cmd[0], F_OK) != 0)
		ft_error(cmd[0], 127, " No such file or directory\n");
	if (access(cmd[0], R_OK) != 0)
		ft_error(cmd[0], 126, " Permission denied\n");
 	if (execve(cmd[0], cmd, envp) == -1)
		ft_error(cmd[0], 126, " command not found\n");
}
