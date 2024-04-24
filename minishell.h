/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:48:14 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/23 13:06:58 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer/lexer.h"
# include "Libft/libft.h"
# include "exec/pipex.h"
# include "parsing/parsing.h"
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

void	minishell_loop(void);
void	handler_signals(int sign);
void	ft_exit(t_token *token);

#endif
