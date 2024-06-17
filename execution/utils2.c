/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:01:11 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/12 17:05:15 by vnavarre         ###   ########.fr       */
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
		main->exit_code = ft_exit(main, token->value);
	}
	free_all(main);
}

static void	exec_else(char **cmd, char **envp, t_main *main, char *str)
{
	char	*path;
	char	*tmp;
	char	*clean;

	tmp = NULL;
	free(str);
	if (count_quotes(cmd[0]))
		clean = clean_str(cmd[0]);
	else
		clean = ft_strdup(cmd[0]);
	path = f_path(clean, envp);
	if (!path)
	{
		tmp = ft_strdup(cmd[0]);
		free(clean);
		ft_error(tmp, 127, " command not found\n", main);
	}
	if (execve(path, cmd, envp) == -1)
	{
		tmp = cmd[0];
		free(path);
		free(clean);
		ft_error(tmp, EXIT_FAILURE, " command not found\n", main);
	}
}

void	exec_cmd(char **cmd, char **envp, t_main *main)
{
	t_dir	*directory;
	char	*tmp;
	char	*clean;

	clean = clean_str(cmd[0]);
	tmp = ft_strdup(clean);
	free(clean);
	if (!ft_env_exists("PATH", main))
		ft_error(tmp, 127, " command not found\n", main);
	if (tmp[0] == '/' || (tmp[0] == '.' && tmp[1] == '/'))
	{
		directory = opendir(cmd[0]);
		if (directory != NULL)
			ft_error(tmp, 126, " Is a directory\n", main);
		if (access(tmp, F_OK) != 0)
			ft_error(tmp, 127, " No such file or directory\n", main);
		if (access(tmp, R_OK) != 0)
			ft_error(tmp, 126, " Permission denied\n", main);
		if (execve(tmp, cmd, envp) != 0)
			ft_error(tmp, 126, " command not found\n", main);
		else
			free(tmp);
	}
	else
		exec_else(cmd, envp, main, tmp);
}

void	close_all(t_main *main)
{
	close(main->fd[0]);
	close(main->fd[1]);
	close(main->here_doc_stdin);
	close(main->original_stdin);
}
