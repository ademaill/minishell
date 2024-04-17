/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:59:34 by vnavarre          #+#    #+#             */
/*   Updated: 2023/11/14 10:25:13 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dp;
	unsigned char	*sp;

	i = 0;
	if (!dest && !src && n > 0)
		return (NULL);
	dp = (unsigned char *) dest;
	sp = (unsigned char *) src;
	while (i < n)
	{
		dp[i] = sp[i];
		i++;
	}
	return (dp);
}
