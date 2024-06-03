/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:43:20 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/03 16:27:22 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*clean_limiter(char *limiter)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	j = 0;
	str = ft_calloc(sizeof(char), ft_strlen(limiter) + 2);
	if (!str)
		return (NULL);
	if (limiter[i] == '"')
		i++;
	while (limiter[i] && limiter[i] != '"')
	{
		str[j] = limiter[i];
		i++;
		j++;
	}
	str[j] = '\n';
	str[j + 1] = '\0';
	return (str);
}

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
		ft_error("/dev/random", EXIT_FAILURE, " No such file or directory\n");
	r = read(fd, buff, 16);
	if (r == -1)
		ft_error(buff, 126, " No such file or directory\n");
	buff[15] = '\0';
	path = ft_strjoin("/tmp/minish_here_doc_", buff);
	if (path == NULL)
		ft_error(path, EXIT_FAILURE, " No such file or directory\n");
	close(fd);
	return (path);
}
