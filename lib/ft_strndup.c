/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:57:50 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/11 15:22:43 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

char	*ft_strndup(const char *str, int j)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof (char) * (j + 1));
	if (!dest)
		return (NULL);
	while (str[i] && i < j)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
