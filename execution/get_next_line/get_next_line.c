/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:27:18 by vnavarre          #+#    #+#             */
/*   Updated: 2024/04/17 14:30:25 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


static char	*write_line(char *stat)
{
	int		i;
	char	*str;

	i = 0;
	if (!stat[i])
		return (NULL);
	while (stat[i] != '\n' && stat[i] != '\0')
		i++;
	str = ft_calloc_gnl(sizeof(char), (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (stat[i] != '\n' && stat[i] != '\0')
	{
		str[i] = stat[i];
		i++;
	}
	str[i] = stat[i];
	if (str[i] == '\n')
		str[i + 1] = '\0';
	return (str);
}

static char	*copy(char *stat)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (stat[i] != '\n' && stat[i] != '\0')
		i++;
	if (!stat[i])
	{
		free(stat);
		return (NULL);
	}
	str = ft_calloc_gnl(sizeof(char), (ft_strlen_gnl(stat) - i + 1));
	if (!str)
		return (NULL);
	i++;
	while (stat[i])
		str[j++] = stat[i++];
	str[j] = '\0';
	free(stat);
	return (str);
}

static char	*read_line(int fd, char *stat)
{
	char	*buff;
	int		line;

	while (1)
	{
		buff = ft_calloc_gnl(sizeof(char), (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		line = read(fd, buff, BUFFER_SIZE);
		stat = ft_strjoin_gnl(stat, buff);
		if (line <= 0 || ft_strchr_gnl(stat, '\n'))
			break ;
	}
	return (stat);
}

char	*get_next_line(int fd)
{
	static char	*stat;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stat = read_line(fd, stat);
	if (!stat)
		return (NULL);
	str = write_line(stat);
	stat = copy(stat);
	return (str);
}
