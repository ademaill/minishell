/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:01:47 by vnavarre          #+#    #+#             */
/*   Updated: 2023/11/03 17:21:53 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_int(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			i;
	int			size;
	char		*nbr;

	nb = n;
	i = 0;
	size = size_int(n);
	nbr = malloc(sizeof(char) * (size + 1));
	if (nbr == NULL)
		return (NULL);
	if (n == 0)
		nbr[0] = '0';
	if (n < 0)
	{
		nb *= -1;
		nbr[i++] = '-';
	}
	while (nb != 0)
	{
		nbr[--size] = ((nb % 10) + '0');
		nb = nb / 10;
	}
	nbr[size_int(n)] = '\0';
	return (nbr);
}
