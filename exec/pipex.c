/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:34:02 by vnavarre          #+#    #+#             */
/*   Updated: 2024/04/18 10:28:39 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	mult_process(char *cmd, char **envp)
{
	pid_t	rd;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error();
	rd = fork();
	if (rd == -1)
		ft_error();
	if (rd == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_cmd(cmd, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(rd, NULL, 0);
	}
}

void	child_process(char **av, char **envp, int *fd)
{
	int in;

	in = open(av[1], O_RDONLY, 0777);
	if (in == -1)
		ft_error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(in);
	close(fd[1]);
	close(fd[0]);
	exec_cmd(av[2], envp);
}

void	parent_process(char **av, char **envp, int *fd)
{
	int	out;

	out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out == -1)
		ft_error();
	dup2(fd[0], STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(out);
	close(fd[0]);
	close(fd[1]);
	exec_cmd(av[3], envp);
}

void	mult_pipe(int ac, char **av, char **envp)
{
	int		i;
	int		in;
	int		out;
	char	*path;

	i = 0;
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		i = 3;
		out = open_file(av[ac - 1], 0);
		path = here_doc(av[2]);
		in = open_file(path, 2);
		dup2(in, STDIN_FILENO);
		close(in);
		unlink(path);
	}
	else
	{
		i = 2;
		in = open_file(av[1], 2);
		out = open_file(av[ac - 1], 1);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	while (i < ac - 2)
		mult_process(av[i++], envp);
	dup2(out, STDOUT_FILENO);
	close(out);
	exec_cmd(av[ac - 2], envp);
}


int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			ft_error();
		pid = fork();
		if (pid == -1)
			ft_error();
		if (pid == 0)
			child_process(av, envp, fd);
		waitpid(pid, NULL, 0);
		parent_process(av, envp, fd);

	}
	else if (ac > 5)
		mult_pipe(ac, av, envp);
	else
	{
		ft_putstr_fd("Error : Wrong number of args.\n", 2);
	}
	return (0);
}
