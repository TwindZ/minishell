/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:23:51 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/28 17:12:21 by emlamoth         ###   ########.fr       */
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
		if(data->child > 0)
		{
			kill(data->child, SIGQUIT);
			mini_reset(data);
			ft_putstr_fd("\n", 1);
			rl_on_new_line();
			// rl_redisplay();
		}	
		else
		{
			ft_putstr_fd("\n", 1);
			rl_on_new_line();
			rl_redisplay();
		}

	}
}


// rl_on_new_line,
// rl_replace_line, rl_redisplay,