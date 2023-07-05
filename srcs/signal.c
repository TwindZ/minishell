/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:23:51 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/04 22:10:16 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler(int sig)
{
	t_data *data;
	
	(void) sig;
	data = ft_init_data(NULL);
	
	if(data->hdprocess)
	{
		exit(1);
	}
	else if (data->pid.count > 0)
	{
		data->pid.index = 0;
		signal(SIGQUIT, SIG_DFL);
		while(data->pid.count)
			{
				kill(data->pid.pid[data->pid.index], SIGQUIT);
				data->pid.count--;
				data->pid.index++;
			}
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		mini_reset(data);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
		
	}
	// else if(sig == SIGCHLD)
	// {
	// }
}
