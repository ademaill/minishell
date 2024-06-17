/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:08:40 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/13 14:18:56 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**clean_tab(char **src)
{
	int		i;
	char	**tab;

	i = 1;
	tab = ft_calloc(sizeof(char *), ft_len_tab(src) + 1);
	tab[0] = ft_strdup(src[0]);
	while (src[i])
	{
		tab[i] = clean_str(src[i]);
		i++;
	}
	return (tab);
}

static void	end_process(int *fd, t_token *token, t_main *main)
{
	(void)fd;
	close(main->fd[0]);
	close(main->fd[1]);
	close(main->original_stdin);
	close(main->here_doc_stdin);
	if (token->type != __cmdgr)
	{
		if (main->hpath)
			free(main->hpath);
		free_all(main);
		exit(0);
	}
	if (is_builtins(token) == 1)
	{
		exec_builtins(token, main);
		exit(EXIT_SUCCESS);
	}
	else
	{
		main->cmd_cpy = clean_tab(token->value);
		exec_cmd(main->cmd_cpy, main->envp, main);
	}
}

void	ft_process(t_token *token, t_main *main, int *fd, bool last)
{
	int		in;
	int		out;
	bool	heredoc;

	heredoc = false;
	in = do_in(token, main, &heredoc);
	if (in)
		dup2(in, STDIN_FILENO);
	if (in)
		close(in);
	if (heredoc)
		unlink(main->hpath);
	out = do_out(token, main);
	if (out)
		dup2(out, STDOUT_FILENO);
	if (!last && !out)
		dup2(fd[1], STDOUT_FILENO);
	if (out)
		close(out);
	end_process(fd, token, main);
}
