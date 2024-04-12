/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:19:25 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/04 11:41:20 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	if ((!s && len == 0) || !s)
		return (NULL);
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	i = 0;
	if (start >= ft_strlen(s))
	{
		str = ft_calloc(sizeof(char), 1);
		return (str);
	}
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[start + i] != '\0' && len-- > 0)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
