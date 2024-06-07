/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:23:31 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/07 11:40:22 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			path = clean_str(tmp->value[1]);
			in = open(path, O_RDONLY, 0777);
			free(path);
			*heredoc = false;
			if (in == -1)
				ft_error(tmp->value[1], 1, " No such file or directory\n");
		}
		else if (tmp->type == __here_doc)
		{
			if (in)
				close(in);
			if (main->hpath)
				free(main->hpath);
			here_doc(tmp->value[1], main);
			in = open(main->hpath, O_RDONLY, 0777);
			if (in == -1)
				ft_error(main->hpath, 1, " No such file or directory\n");
			*heredoc = true;
		}
		tmp = tmp->next;
	}
	return (in);
}

int	do_out(t_token *token)
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
		{
			path = clean_str(tmp->value[1]);
			out = open_file(path, 1);
			free(path);
		}
		if (tmp->type == __append)
		{
			path = clean_str(tmp->value[1]);
			out = open_file(path, 0);
			free(path);
		}
		tmp = tmp->next;
	}
	return (out);
}
