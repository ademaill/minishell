/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:58:03 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/29 14:29:38 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		size_str;
	char	*dup;
	int		i;

	size_str = ft_strlen(s);
	dup = ft_calloc(sizeof(char), (size_str + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}
