/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:45:28 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/17 14:25:54 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_received;

int	main(int ac, char **av, char **envp)
{
	t_main	*data;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_main));
	ft_memset(data, 0, sizeof(t_main));
	if (!envp[0])
		data->envp = NULL;
	data->envp = envp;
	data->env = ft_env_int(data->envp);
	ft_got_signal(1);
	minishell_loop(data);
	free(data);
	return (0);
}
