/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:43:20 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/17 14:13:57 by vnavarre         ###   ########.fr       */
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
		ft_error("/dev/random", EXIT_FAILURE);
	r = read(fd, buff, 16);
	if (r == -1)
		ft_error(buff, 126);
	buff[15] = '\0';
	path = ft_strjoin("/tmp/minish_here_doc_", buff);
	if (path == NULL)
		ft_error(path, EXIT_FAILURE);
	close(fd);
	return (path);
}
