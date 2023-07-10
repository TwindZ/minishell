/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:23:51 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/10 17:32:16 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler(int sig)
{
	t_data *data;
	
	data = ft_init_data(NULL);
	if(sig == SIGINT)
	{
		if(data->hdprocess)
		{
			rl_replace_line("", 0);
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_on_new_line();
			exit(45);
		}
		else if (data->exeprocess)
		{
			rl_replace_line("", 0);
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_on_new_line();
		}	
		else
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}	
	}
	mini_reset(data);
}
