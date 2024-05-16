/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:34:02 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/16 12:58:26 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


static void	ft_process(t_token *token, t_main *main, int *fd, bool last)
{
	int	in;
	int	out;

	in = do_in(token, main);
	out = do_out(token);
	if (in == -1 || out == -1)
		ft_error();
	if (in)
		dup2(in, STDIN_FILENO);
	if (out)
		dup2(out, STDOUT_FILENO);
	if (!last && !out)
		dup2(fd[1], STDOUT_FILENO);
	if (in)
		close(in);
	if (out)
		close(out);
	close(fd[0]);
	close(fd[1]);
	exec_cmd(token->value, main->envp);
}

int	mult_process(t_token *token, t_main *main, bool last)
{
	pid_t	rd;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error();
	rd = fork();
	if (rd == -1)
		ft_error();
	printf("%s\n", token->value[0]);
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
	printf("%d\n", pipecount);
	main->pid = malloc(sizeof(int *) * pipecount + 1);
	while (i <= pipecount + 1)
	{
		last = false;
		if (i == pipecount + 1)
			last = true;
		if (is_builtins(ft_find(main->token, i)))
			exec_builtins(ft_find(main->token, i), main);
		else
			main->pid[j] = mult_process(ft_find(main->token, i), main, last);
		i++;
		j++;
	}
	printf("jsp\n");
	//ft_process(ft_find(token, i), envp, fd, true, true);
}

int	  ft_exec(t_main *main)
{
	int		fd[2];
	//pid_t	pid;
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
	/*if (pipecount == 1)
	{
		if (pipe(fd) == -1)
			ft_error();
		pid = fork();
		if (pid == -1)
			ft_error();
		if (pid == 0)
			ft_process(ft_find(main->token, 1), main->envp, fd, false);
		waitpid(pid, NULL, 0);
		ft_process(ft_find(main->token, 2), main->envp, fd, true);
	}*/
	if (pipecount == 0)
		ft_process(main->token, main, fd, true);
	else
		mult_pipe(pipecount, main, fd);
	//else if (pipecount == 0)
		//ft_process(ft_find(main->token, 1), main->envp, fd, true);
	dup2(original_stdint, STDIN_FILENO);
	close(original_stdint);
	return (0);
}

