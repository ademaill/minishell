/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:19:26 by vnavarre          #+#    #+#             */
/*   Updated: 2023/10/31 13:10:02 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char			*ps;
	unsigned char			sc;
	size_t					i;

	ps = s;
	sc = c;
	i = 0;
	while (i < n)
	{
		ps[i] = sc;
		i++;
	}
	return (ps);
}
