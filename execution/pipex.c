/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:34:02 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/05 17:00:11 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**clean_tab(char **src)
{
	int		i;
	char	**tab;

	i = 1;
	tab = ft_calloc(sizeof(char *), ft_len_tab(src) + 1);
	tab[0] = src[0];
	while (src[i])
	{
		tab[i] = clean_str(src[i]);
		i++;
	}
	return (tab);
}

static void	ft_process(t_token *token, t_main *main, int *fd, bool last)
{
	int		in;
	int		out;
	bool	heredoc;
	char	**tab;

	heredoc = false;
	tab = NULL;
	in = do_in(token, main, &heredoc);
	out = do_out(token);
	if (token->type != __cmdgr)
		exit(0);
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
	close(fd[0]);
	close(fd[1]);
	if (is_builtins(token) == 1)
	{
		exec_builtins(token, main);
		exit(EXIT_SUCCESS);
	}
	else
	{
		tab = clean_tab(token->value);
		exec_cmd(tab, main->envp);
	}
}

int	check_parents_builtins(t_token *token, t_main *main)
{
	if (ft_strncmp(token->value[0], "exit", 5) == 0 && !token->prev && !token->next)
	{
		printf("exit\n");
		main->exit_code = ft_exit(main, main->token->value);
	}
	else if (ft_strncmp(token->value[0], "cd", 3) == 0)
		main->exit_code = ft_cd(main->token->value, main);
	else if (ft_strncmp(token->value[0], "unset", 6) == 0)
		main->exit_code = ft_unset(main->token->value, main);
	else if (ft_strncmp(token->value[0], "export", 7) == 0 && token->value[1] && !token->prev && !token->next)
		main->exit_code = ft_export(main->token->value, main);
	else
		return (0);
	return (1);
}

int	mult_process(t_token *token, t_main *main, bool last)
{
	pid_t	rd;
	int		fd[2];

	if (check_parents_builtins(token, main))
		return (0);
	if (pipe(fd) == -1)
		ft_error("error pipe", EXIT_FAILURE, "pipe\n");
	rd = fork();
	if (rd == -1)
		ft_error("error fork", EXIT_FAILURE, "fork\n");
	if (rd == 0)
	{
		ft_process(token, main, fd, last);
	}
	else
	{
		if	(!last)
			dup2(fd[0], STDIN_FILENO);
		//else
		//	close(STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
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
		tmp = ft_find(main->token, i);
		main->pid[j] = mult_process(tmp, main, last);
		j++;
		i++;
	}
	main->pid[j] = 0;
}

int	ft_exec(t_main *main)
{
	int		pipecount;
	int		original_stdin;
	t_token	*tmp;

	pipecount = 0;
	tmp = main->token;
	original_stdin = dup(STDIN_FILENO);
	main->here_doc_stdin = dup(STDIN_FILENO);
	while (tmp)
	{
		if (tmp->type == __pipe)
			pipecount++;
		tmp = tmp->next;
	}
	ft_got_signal(0);
	mult_pipe(pipecount, main);
	ft_got_signal(1);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	close(main->here_doc_stdin);
	return (0);
}
