/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:23:31 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/13 13:58:56 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	do_in_next(int in, t_main *main, t_token *tmp, bool *heredoc)
{
	if (in)
		close(in);
	if (main->hpath)
		free(main->hpath);
	here_doc(tmp->value[1], main);
	in = open(main->hpath, O_RDONLY, 0777);
	if (in == -1)
		close_all(main);
	if (in == -1)
		ft_error(main->hpath, 1, " No such file or directory\n", main);
	*heredoc = true;
	return (in);
}

static int	in_redirect_in(int in, t_main *main, t_token *tmp, bool *heredoc)
{
	char	*path;

	path = NULL;
	if (in)
		close(in);
	path = clean_str(tmp->value[1]);
	in = open(path, O_RDONLY, 0777);
	if (access(path, R_OK) != 0 && access(path, F_OK) == 0)
	{
		close(in);
		close_all(main);
		ft_error(path, 1, "Permission denied\n", main);
	}
	free(path);
	*heredoc = false;
	return (in);
}

int	do_in(t_token *token, t_main *main, bool *heredoc)
{
	t_token	*tmp;
	int		in;
	char	*path;

	tmp = token;
	path = NULL;
	in = 0;
	while (tmp->prev && tmp->prev->type != __pipe)
		tmp = tmp->prev;
	while (tmp && tmp->type != __pipe)
	{
		if (tmp->type == __redirect_in)
		{
			in = in_redirect_in(in, main, tmp, heredoc);
			if (in == -1)
				close_all(main);
			if (in == -1)
				ft_error(ft_strdup(tmp->value[1]), 1,
					"No such file or directory\n", main);
		}
		else if (tmp->type == __here_doc)
			in = do_in_next(in, main, tmp, heredoc);
		tmp = tmp->next;
	}
	return (in);
}

static int	do_out_append(char *path, t_token *tmp, int out, t_main *main)
{
	path = clean_str(tmp->value[1]);
	out = open_file(path, 0, main);
	free(path);
	return (out);
}

int	do_out(t_token *token, t_main *main)
{
	t_token	*tmp;
	int		out;
	char	*path;

	path = NULL;
	tmp = token;
	out = 0;
	while (tmp->prev && tmp->prev->type != __pipe)
		tmp = tmp->prev;
	while (tmp && tmp->type != __pipe)
	{
		if (tmp->type == __redirect_out)
			out = do_redirect_out(out, path, tmp, main);
		if (tmp->type == __append)
		{
			if (out)
				close(out);
			out = do_out_append(path, tmp, out, main);
		}
		tmp = tmp->next;
	}
	return (out);
}
