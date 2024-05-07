/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:23:31 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/07 15:32:01 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.c"

int	do_in(t_main *main)
{
	t_token	*tmp;
	int		in;

	tmp = main->token;
	in = 0;
	while (tmp && tmp->type != __pipe)
	{
		if (tmp->type == __redirect_in)
		{
			in = open(tmp->value[1], O_RDONLY, 0777);
			if (in == -1)
				ft_error();
		}
		else if (tmp->type == __here_doc)
			in = open_file(here_doc(tmp->value[1]), 2);
		tmp = tmp->next;
	}
	return (in);
}

int	do_out(t_main *main)
{
	t_token	*tmp;
	int		out;

	tmp = main->token;
	out = 0;
	while (tmp && tmp->type != __pipe)
	{
		if (tmp->type == __redirect_out)
			out = open_file(tmp->value, 1);
		if (tmp->type == __append)
			out = open_file(tmp->value, 0);
		tmp = tmp->next;
	}
	return (out);
}
