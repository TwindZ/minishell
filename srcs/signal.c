/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:23:51 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/03 17:10:42 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler(int sig)
{
	t_data *data;

	data = ft_init_data(NULL);
	
	if(sig == SIGINT)
	{
		if(data->child == 0)
		{
			exit(1);
		}	
		// else if (data->hdprocess)
		// {
		// 	ft_printf("SIGCHLD\n");
		// 	// kill(0, SIGQUIT);
		// 	data->hdprocess = 0;
		// 	ft_putstr_fd("\n", 1);
		// 	rl_on_new_line();
		// 	rl_redisplay();
		// }
		else
		{
		// ft_printf("Ssalut\n");
			ft_putstr_fd("\n", 1);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	// else if(sig == SIGCHLD)
	// {
	// }
		// ft_printf("%d\n", sig);
}
