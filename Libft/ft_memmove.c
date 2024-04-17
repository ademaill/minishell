/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:26:33 by vnavarre          #+#    #+#             */
/*   Updated: 2023/11/07 15:23:27 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dp;
	unsigned char	*sp;

	i = -1;
	if (!dest && !src && n > 0)
		return (NULL);
	dp = (unsigned char *)dest;
	sp = (unsigned char *)src;
	if (dp > sp)
	{
		while (n > 0)
		{
			dp[n - 1] = sp[n - 1];
			n--;
		}
	}
	else
	{
		while (++i < n)
			dp[i] = sp[i];
	}
	return (dest);
}
