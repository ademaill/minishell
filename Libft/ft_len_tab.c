/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:27:26 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/25 17:28:49 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_len_tab(char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
		i++;
	return (i);
}
