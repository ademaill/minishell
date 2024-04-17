/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:39:51 by vnavarre          #+#    #+#             */
/*   Updated: 2023/11/03 16:44:03 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ps;
	unsigned char	pc;
	size_t			i;

	ps = (unsigned char *) s;
	pc = c;
	i = 0;
	while (i < n)
	{
		if (ps[i] == pc)
			return (&ps[i]);
		i++;
	}
	return (NULL);
}
