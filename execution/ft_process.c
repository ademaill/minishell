/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:08:40 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/06 17:53:45 by ademaill         ###   ########.fr       */
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

static void	end_process(int *fd, t_token *token, t_main *main)
{
	char	**tab;

	tab = NULL;
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
		exec_cmd(tab, main->envp, main);
	}
}

void	ft_process(t_token *token, t_main *main, int *fd, bool last)
{
	int		in;
	int		out;
	bool	heredoc;

	heredoc = false;
	out = do_out(token);
	in = do_in(token, main, &heredoc);
	if (token->type != __cmdgr)
		exit(0);
	if (in)
		dup2(in, STDIN_FILENO);
	if (heredoc)
		unlink(main->hpath);
	if (out)
		dup2(out, STDOUT_FILENO);
	if (!last && !out)
		dup2(fd[1], STDOUT_FILENO);
	if (out)
		close(out);
	if (in)
		close(in);
	end_process(fd, token, main);
}
