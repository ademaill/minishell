/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:43:20 by vnavarre          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/17 13:57:16 by ademaill         ###   ########.fr       */
=======
/*   Updated: 2024/04/18 09:31:09 by vnavarre         ###   ########.fr       */
>>>>>>> ccf0314b711a31f9f62f1f0cf593f3dedfa369e8
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
	//if (fd == -1)
		//message error
	r = read(fd, buff, 16);
	//if (r == -1)
		//message error
	path = ft_strjoin("/tmp/minish_here_doc_", buff);
	//if (path == NULL)
		//error message
	close(fd);
	return (path);
}
