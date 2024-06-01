/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:47:46 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/01 14:12:59 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*f_path(char *cmd, char **envp)
{
	char	**all_paths;
	char	*path;
	int		i;
	char	*tmp;

	i = 0;
	while ((ft_strnstr(envp[i], "PATH", 4)) == 0)
		i++;
	all_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		tmp = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
		free(path);
	}
	free_tab(all_paths);
	return (0);
}

void	ft_error(char *str, int code, char *error)
{
	ft_putstr_fd(error, 2);
	free(str);
	exit(code);
}

void	exec_cmd(char **cmd, char **envp)
{
	char	*path;
	char	*tmp;
	DIR*	directory;
	tmp = NULL;

	if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
	{
		directory = opendir(cmd[0]);
		if(directory != NULL)
			ft_error(cmd[0], 126, " Is a directory\n");
		if (access(cmd[0], F_OK) != 0)
			ft_error(cmd[0], 127, " No such file or directory\n");
		if (access(cmd[0], R_OK) != 0)
			ft_error(cmd[0], 126, " Permission denied\n");
 		if (execve(cmd[0], cmd, envp) == -1)
			ft_error(cmd[0], 126, " command not found\n");
	}
	else
	{
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
}

int	open_file(char *name, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(name, O_RDONLY, 0777);
	if (file == -1)
		ft_error(name, EXIT_FAILURE, " Permission denied\n");
	return (file);
}

t_token	*ft_find(t_token *token, int i)
{
	int	count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	while (token)
	{
		if (token->type == __cmdgr)
			count++;
		if (count == i)
			return (token);
		token = token->next;
	}
	return (tmp);
}
