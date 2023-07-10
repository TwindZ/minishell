/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:23:51 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/10 07:53:53 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler(int sig)
{
	t_data *data;
	
	data = ft_init_data(NULL);
	
	// if(sig == SIGQUIT && data->pid.pid == 0)
	// {
	// 	// ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	// 	rl_replace_line("Quit : 3\n", 0);
	// 	rl_on_new_line();
	// }
	if(sig == SIGINT)
	{
		if(data->hdprocess)
		{
			ft_printf("hd");
			rl_replace_line("", 0);
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_on_new_line();
			exit(45);
		}
		else if (data->exeprocess)
		{
			ft_printf("exe");
			rl_replace_line("", 0);
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_on_new_line();
			// rl_redisplay();
		}	
		else
		{
			ft_printf("else");
			rl_replace_line("", 0);
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_on_new_line();
			rl_redisplay();
		}	
	}
	mini_reset(data);
}
