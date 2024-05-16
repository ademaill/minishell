/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:47:46 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/10 09:55:17 by vnavarre         ###   ########.fr       */
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

void	ft_error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	exec_cmd(char **cmd, char **envp)
{
	char	*path;

	if (cmd[0][0] == '/')
	{
		if (execve(cmd[0], cmd, envp) == -1)
			ft_error();
	}
	else
	{
		path = f_path(cmd[0], envp);
		if (!path)
		{
			free_tab(cmd);
			ft_error();
		}
		if (execve(path, cmd, envp) == -1)
		{
			free(path);
			ft_error();
		}
	}
}

int	open_file(char	*name, int i)
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
		ft_error();
	return (file);
}

t_token	*ft_find(t_token *token, int i)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == __cmdgr)
			count++;
		if (count == i)
			return (token);
		token = token->next;
	}
	return (token);
}
