/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:01:58 by vnavarre          #+#    #+#             */
/*   Updated: 2023/11/09 08:38:05 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	i = 0;
	if ((!s && len == 0) || !s)
		return (NULL);
	if (len >= ft_strlen(s))
		len = (ft_strlen(s) - start);
	if (start >= ft_strlen(s))
	{
		str = ft_calloc(sizeof(char), 1);
		return (str);
	}
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[start + i] != '\0' && len-- > 0)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
