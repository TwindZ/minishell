/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:23:51 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/04 17:57:08 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler(int sig)
{
	t_data *data;

	data = ft_init_data(NULL);
	
	if(sig == SIGINT)
	{
		if(data->pid.pid[data->pid.index] == 0)
		{
			exit(1);
		}
		else
		{
			mini_reset(data);
			ft_putstr_fd("\n", 1);
			rl_on_new_line();
			rl_redisplay();
			
		}
	}
	// else if(sig == SIGCHLD)
	// {
	// }
}
