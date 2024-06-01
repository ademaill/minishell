/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:05:06 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/01 15:43:04 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_rest_gnl(int fd, char *line)
{
	free(line);
	close(fd);
	line = get_next_line(fd);
	free(line);
}

static char	*ft_expand_here_doc(char *str, t_main *main)
{
	char	*ret ;
	int		i;

	i = 0;
	ret = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
			ret = ft_strjoin(ret, ft_handle_dollars(str, &i, main));
		else if (str[i] == '"')
			ret = ft_strjoin(ret, ft_handle_d_quotes(str, &i));
		else if (str[i] == '\'')
			ret = ft_strjoin(ret, ft_handle_s_quotes(str, &i, true));
		else
			ret = ft_strjoin(ret, ft_handle_str(str, &i));
	}
	return (ret);
}

static char	*clean_limiter(char *limiter)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	j = 0;
	str = ft_calloc(sizeof(char), ft_strlen(limiter));
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

char	*here_doc(char *limiter, t_main *main)
{
	int		fd;
	char	*line;
	char	*path;
	char	*tmp;

	path = rand_path();
	tmp = limiter;
	limiter = clean_limiter(limiter);
	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 0644);
	write(STDOUT_FILENO, ">", 1);
	line = get_next_line(STDIN_FILENO);
	printf("%zu\n", ft_strlen(limiter));
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0 || (ft_strlen(line) - 1) == ft_strlen(limiter))
	{
		printf("%zu\n", ft_strlen(line));
		write(STDOUT_FILENO, ">", 1);
		if ((tmp[0] != '"' && tmp[ft_strlen(tmp) - 1] != '"') && (tmp[0] != '\'' && tmp[ft_strlen(tmp) - 1] != '\''))
			line = ft_expand_here_doc(line, main);
		if (ft_strncmp(line, "^\\", 2) == 0)
			{
				free(line);
				continue ;
			}
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
	}
	free_rest_gnl(fd, line);
	close(fd);
	return (path);
}
