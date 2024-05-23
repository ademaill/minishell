/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:10:32 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/22 12:36:23 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(const char a)
{
	if (a == ' ' || (a >= '\t' && a <= '\r'))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	pos;
	int	result;

	i = 0;
	pos = 1;
	result = 0;
	while (ft_isspace(nptr[i]) == 1)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			pos = pos * (-1);
		i++;
	}
	while (ft_isdigit(nptr[i]) == 1)
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	result = result * pos;
	return (result);
}
