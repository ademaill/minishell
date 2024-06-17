/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:44:56 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/08 17:06:37 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	do_redirect_out(int out, char *path, t_token *tmp, t_main *main)
{
	if (out)
		close(out);
	path = clean_str(tmp->value[1]);
	out = open_file(path, 1, main);
	free(path);
	return (out);
}
