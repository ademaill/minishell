/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:47:46 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/13 14:18:55 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	while_path(char **envp, int *i)
{
	while (envp[(*i)] && (ft_strnstr(envp[(*i)], "PATH", 4)) == 0)
	{
		if (envp[(*i)] == NULL)
		{
			ft_putstr_fd("Error, Path not set.\n", 2);
			exit(0);
		}
		(*i)++;
	}
}

char	*f_path(char *cmd, char **envp)
{
	char	**all_paths;
	char	*path;
	int		i;
	char	*tmp;

	i = 0;
	if (!envp || !envp[0])
		return (NULL);
	while_path(envp, &i);
	if (!envp[i])
		return (NULL);
	all_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		tmp = ft_strjoin(all_paths[i], "/", false);
		path = ft_strjoin(tmp, cmd, false);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
		free(path);
	}
	free_tab(all_paths);
	return (0);
}

void	ft_error(char *str, int code, char *error, t_main *main)
{
	(void)str;
	ft_putstr_fd(error, 2);
	if (main->hpath)
		free(main->hpath);
	free_all(main);
	if (str)
		free(str);
	exit(code);
}

int	open_file(char *name, int i, t_main *main)
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
		close_all(main);
	if (file == -1)
		ft_error(name, EXIT_FAILURE, " Permission denied\n", main);
	return (file);
}
