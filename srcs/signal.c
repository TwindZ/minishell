/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:23:51 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/28 13:03:58 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	t_data *data;

	data = ft_init_data(NULL);
	
	(void)	sig;
	(void)	info;
	(void)	ucontext;
	if(sig == SIGINT)
	{
		// ft_printf("CTRL-C");
		ft_putstr_fd("\n", 1);
		// rl_on_new_line();
		rl_redisplay();
		// rl_replace_line();
	}
}


// rl_on_new_line,
// rl_replace_line, rl_redisplay,