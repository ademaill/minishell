/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:45:34 by vnavarre          #+#    #+#             */
/*   Updated: 2023/11/07 16:16:10 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	is_in_set(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	start;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (is_in_set(s1[i], set) == 1)
		i++;
	while (is_in_set(s1[j], set) == 1 && j >= i)
		j--;
	start = 0;
	str = malloc((j - i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (start < (j - i + 1))
	{
		str[start] = s1[start + i];
		start++;
	}
	str[start] = '\0';
	return (str);
}
