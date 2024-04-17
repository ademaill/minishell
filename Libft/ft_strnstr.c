/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:59:15 by vnavarre          #+#    #+#             */
/*   Updated: 2023/11/04 12:54:44 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *) big;
	if ((!big || !little) && len == 0)
		return (NULL);
	if (little[i] == '\0')
		return (str);
	if (ft_strlen(big) >= ft_strlen(little))
	{
		while ((big[i] != '\0') && (i < len) && (len - i >= ft_strlen(little)))
		{
			while (big[i] == little[0] && ft_strcmp((big + i), little) == 0)
				return (str + i);
			i++;
		}
	}
	return (NULL);
}
