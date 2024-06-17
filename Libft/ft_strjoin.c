/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:36:06 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/12 16:47:06 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char const *dest, char const *src, char *str)
{
	int		i;
	size_t	j;

	i = 0;
	while (dest[i] != '\0')
	{
		str[i] = dest[i];
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		str[j + i] = src[j];
		j++;
	}
	str[j + i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2, bool mal)
{
	size_t	size;
	char	*str;

	if (!s1 && s2)
		return (s2);
	if (s1 && !s2)
		return (s1);
	if (!s1 && !s2)
		return (NULL);
	size = (ft_strlen(s1) + ft_strlen(s2));
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str = ft_strcat(s1, s2, str);
	if (mal)
	{
		free(s1);
		free(s2);
	}
	return (str);
}
