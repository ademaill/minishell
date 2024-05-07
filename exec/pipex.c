/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:34:02 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/07 13:50:23 by vnavarre         ###   ########.fr       */
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

void	child_process(t_token *token, t_env *env, int *fd)
{
	int	in;
	int	out;

	if (token->prev->type == __here_doc)
		in = open_file(here_doc(token->prev->value[1]), 2);
	else if (token->prev->type == __redirect_in)
		in = open(token->prev->value[1], O_RDONLY, 0777);
	else if (token->prev->type == __redirect_out)
		out = open_file(token->prev->value[1], 1);
	if (in == -1 || out == -1)
		ft_error();
	if (in)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	else
		dup2(fd[0], STDIN_FILENO);
	if (out)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exec_cmd(token->value, env);
}

void	parent_process(t_token *token, t_env *env, int *fd)
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

int	exec(t_main *main)
{
	int		fd[2];
	pid_t	pid;
	int		pipecount;

	pipecount = 0;
	while (main->token)
	{
		if (main->token->type == __pipe)
			pipecount++;
		main->token = main->token->next;
	}
	if (pipecount == 1)
	{
		if (pipe(fd) == -1)
			ft_error();
		pid = fork();
		if (pid == -1)
			ft_error();
		if (pid == 0)
			child_process(ft_find(main->token, 1), main->env, fd);
		waitpid(pid, NULL, 0);
		parent_process(ft_find(main->token, 2), main->env, fd);
	}
	else if (pipecount > 1)
		mult_pipe(pipecount, main->token->value, main->env);
	else
	{
		ft_putstr_fd("Error : Wrong number of args.\n", 2);
	}
	return (0);
}
