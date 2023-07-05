/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:23:51 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/05 18:16:26 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler(int sig)
{
	t_data *data;
	
	data = ft_init_data(NULL);
	mini_reset(data);
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	
	// if(sig == SIGQUIT)
	
	if(sig == SIGINT)
	{
		if(data->hdprocess)
			exit(45);
		else
			rl_redisplay();
	}
}
