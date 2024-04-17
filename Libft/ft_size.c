/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:08:41 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/17 10:08:55 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size(char *line, int *i)
{
	int	count;
	int	j;

	count = 0;
	j = 0;
	while (line[(*i) + j] && line[(*i) + j] != ' ')
	{
		j++;
		count++;
	}
	return (count);
}
