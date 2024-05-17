/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:12:33 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/17 12:21:16 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4242
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

char	*get_next_line(int fd);
int		ft_slen_gnl(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_strchr_gnl(char *s, int c);
char	*ft_calloc_gnl(int size, int len);

#endif
