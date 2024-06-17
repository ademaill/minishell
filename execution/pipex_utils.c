/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:37:53 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/08 15:57:51 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../minishell.h"

static bool	is_herdoc(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->prev && tmp->prev->type != __pipe)
		tmp = tmp->prev;
	while (tmp && tmp->type != __pipe)
	{
		if (tmp->type == __here_doc)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	else_pipex(bool last, t_main *main, t_token *token, pid_t rd)
{
	if (!last)
		dup2(main->fd[0], STDIN_FILENO);
	else
		close(STDIN_FILENO);
	if (is_herdoc(token))
		waitpid(rd, NULL, 0);
}

void	close_process(t_main *main)
{
	ft_got_signal(1);
	close(main->fd[0]);
	close(main->fd[1]);
}
