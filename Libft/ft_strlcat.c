/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:02:51 by vnavarre          #+#    #+#             */
/*   Updated: 2023/11/04 11:28:52 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((!src || !dst) && size == 0)
		return (0);
	j = ft_strlen(dst);
	if (size <= j)
		return (size + ft_strlen(src));
	while (src[i] != '\0' && i + j < (size - 1))
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (j + ft_strlen(src));
}
