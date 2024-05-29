/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:34:02 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/29 11:25:49 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_process(t_token *token, t_main *main, int *fd, bool last)
{
	int		in;
	int		out;
	bool	heredoc;

	heredoc = false;
	in = do_in(token, main, &heredoc);
	out = do_out(token);
	if (in)
		dup2(in, STDIN_FILENO);
	if (heredoc)
		unlink(main->heredoc_path);
	if (out)
		dup2(out, STDOUT_FILENO);
	if (!last && !out)
		dup2(fd[1], STDOUT_FILENO);
	if (in)
		close(in);
	if (out)
		close(out);
	if (!last && !out)
		close(fd[1]);
	exec_cmd(token->value, main->envp);
}

int	mult_process(t_token *token, t_main *main, bool last)
{
	pid_t	rd;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error("error pipe", EXIT_FAILURE);
	rd = fork();
	if (rd == -1)
		ft_error("error fork", EXIT_FAILURE);
	if (rd == 0)
	{
		ft_process(token, main, fd, last);
	}
	else
	{
		if (!last)
			dup2(fd[0], STDIN_FILENO);
		else
			close(STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		return (rd);
	}
	return (0);
}
/*void	process(t_token *token, t_env *env, int *fd)
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
}*/

void	mult_pipe(int pipecount, t_main *main, int *fd)
{
	int		i;
	int		j;
	bool	last;

	i = 1;
	(void)fd;
	j = 0;
	main->pid = ft_calloc(sizeof(int), pipecount + 2);
	while (i <= pipecount + 1)
	{
		last = false;
		if (i == pipecount + 1)
			last = true;
		if (is_builtins(ft_find(main->token, i)) == 1)
			exec_builtins(ft_find(main->token, i), main);
		else
		{
			main->pid[j] = mult_process(ft_find(main->token, i), main, last);
			j++;
		}
		i++;
	}
	main->pid[j] = 0;
}

int	ft_exec(t_main *main)
{
	int		fd[2];
	int		pipecount;
	int		original_stdint;
	t_token	*tmp;

	pipecount = 0;
	tmp = main->token;
	original_stdint = dup(STDIN_FILENO);
	while (tmp)
	{
		if (tmp->type == __pipe)
			pipecount++;
		tmp = tmp->next;
	}
	mult_pipe(pipecount, main, fd);
	dup2(original_stdint, STDIN_FILENO);
	close(original_stdint);
	return (0);
}
