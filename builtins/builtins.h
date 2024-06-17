/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:10:48 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/10 16:36:22 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lst_new(void *content);
void	ft_lst_add_back(t_list **lst, t_list *new);
void	close_in_exit(t_main *main);

#endif
