/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:23:31 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/17 13:56:41 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	do_in(t_token *token, t_main *main, bool *heredoc)
{
	t_token	*tmp;
	int		in;

	tmp = token;
	in = 0;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp && tmp->type != __pipe)
	{
		if (tmp->type == __redirect_in)
		{
			in = open(tmp->value[1], O_RDONLY, 0777);
			*heredoc = false;
			if (in == -1)
				ft_error(tmp->value[1], EXIT_FAILURE);
		}
		else if (tmp->type == __here_doc)
		{
			main->heredoc_path = here_doc(tmp->value[1], main);
			in = open_file(main->heredoc_path, 2);
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

	tmp = token;
	out = 0;
	while (tmp && tmp->type != __pipe)
	{
		if (tmp->type == __redirect_out)
			out = open_file(tmp->value[1], 1);
		if (tmp->type == __append)
			out = open_file(tmp->value[1], 0);
		tmp = tmp->next;
	}
	return (out);
}
