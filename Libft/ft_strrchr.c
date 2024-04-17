/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:05:43 by vnavarre          #+#    #+#             */
/*   Updated: 2023/11/09 08:46:57 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = ft_strlen(s);
	str = (char *) s;
	while (i >= 0)
	{
		if (s[i] == (char) c)
			return (&str[i]);
		i--;
	}
	return (NULL);
}
