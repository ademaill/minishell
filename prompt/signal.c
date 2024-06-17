/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:47:04 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/10 16:40:39 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_fork(int sgn);
void	handle_signal(int sgn, siginfo_t *info, void *context);

void	ft_got_signal(int handle)
{
	struct sigaction	s_sigaction;

	ft_bzero(&s_sigaction, sizeof(s_sigaction));
	s_sigaction.sa_sigaction = handle_signal;
	s_sigaction.sa_flags = SA_SIGINFO;
	if (handle)
	{
		signal(SIGQUIT, SIG_IGN);
		sigaction(SIGINT, &s_sigaction, NULL);
	}
	else
	{
		signal(SIGPIPE, SIG_IGN);
		signal(SIGQUIT, handle_fork);
		signal(SIGINT, handle_fork);
	}
}

void	handle_fork(int sgn)
{
	g_sig_received = sgn;
	printf("\n");
}

void	handle_signal(int sgn, siginfo_t *info, void *context)
{
	(void)context;
	g_sig_received = sgn;
	if (info->si_pid == 0)
		printf("\n");
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
