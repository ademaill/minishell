/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:43:20 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/16 12:58:11 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*rand_path(void)
{
	char	buff[16];
	char	*path;
	int		r;
	int		fd;

	r = 0;
	fd = 0;
	path = NULL;
	fd = open("/dev/random", O_RDONLY, 0644);
	if (fd == -1)
		ft_error();
	r = read(fd, buff, 16);
	if (r == -1)
		ft_error();
	path = ft_strjoin("/tmp/minish_here_doc_", buff);
	if (path == NULL)
		ft_error();
	close(fd);
	return (path);
}
