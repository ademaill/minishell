/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:45:30 by vnavarre          #+#    #+#             */
/*   Updated: 2023/11/14 09:42:46 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*block;
	size_t	total;

	if (nmemb == 0 || size == 0)
		return (ft_calloc(1, 1));
	total = nmemb * size;
	if (total / size != nmemb)
		return (NULL);
	block = malloc(total);
	if (!block)
		return (NULL);
	ft_bzero(block, total);
	return (block);
}
