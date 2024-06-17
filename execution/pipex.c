/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:34:02 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/13 13:51:03 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_parents_builtins(t_token *token, t_main *main)
{
	if (ft_strncmp(token->value[0], "exit", 5) == 0
		&& !token->prev && !token->next)
	{
		printf("exit\n");
		main->exit_code = ft_exit(main, main->token->value);
	}
	else if (ft_strncmp(token->value[0], "cd", 3) == 0)
		main->exit_code = ft_cd(main->token->value, main);
	else if (ft_strncmp(token->value[0], "unset", 6) == 0)
		main->exit_code = ft_unset(main->token->value, main);
	else if (ft_strncmp(token->value[0], "export", 7) == 0
		&& token->value[1] && !token->prev && !token->next)
		main->exit_code = ft_export(main->token->value, main);
	else
		return (0);
	return (1);
}

int	mult_process(t_token *token, t_main *main, bool last)
{
	pid_t	rd;

	if (check_parents_builtins(token, main))
		return (0);
	if (pipe(main->fd) == -1)
		ft_error("error pipe", EXIT_FAILURE, "pipe\n", main);
	rd = fork();
	if (rd == -1)
		ft_error("error fork", EXIT_FAILURE, "fork\n", main);
	if (rd == 0)
	{
		ft_got_signal(0);
		ft_process(token, main, main->fd, last);
	}
	else
	{
		else_pipex(last, main, token, rd);
		close_process(main);
		return (rd);
	}
	return (0);
}

void	mult_pipe(int pipecount, t_main *main)
{
	int		i;
	int		j;
	t_token	*tmp;
	bool	last;

	i = 1;
	j = 0;
	tmp = NULL;
	main->pid = ft_calloc(sizeof(int), pipecount + 2);
	while (i <= pipecount + 1)
	{
		last = false;
		if (i == pipecount + 1)
			last = true;
		tmp = ft_find(main->token, last, i);
		tmp = ft_find_cmdgr(tmp);
		main->pid[j] = mult_process(tmp, main, last);
		j++;
		i++;
	}
	main->pid[j] = 0;
}

int	ft_exec(t_main *main)
{
	int		pipecount;
	t_token	*tmp;

	pipecount = 0;
	tmp = main->token;
	main->here_doc_stdin = dup(STDIN_FILENO);
	main->original_stdin = dup(STDIN_FILENO);
	while (tmp)
	{
		if (tmp->type == __pipe)
			pipecount++;
		tmp = tmp->next;
	}
	mult_pipe(pipecount, main);
	dup2(main->original_stdin, STDIN_FILENO);
	close(main->original_stdin);
	close(main->here_doc_stdin);
	return (0);
}
