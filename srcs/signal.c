/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:23:51 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/27 16:42:05 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Simple minishell signal handler*/
void	sig_handler(int sig)
{
	t_data	*data;

	data = ft_init_data(NULL);
	if (sig == SIGQUIT)
	{
		exit_free(data, 1);
	}
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (data->hdprocess)
		{
			mini_reset(data);
			exit_free(data, 1);
			exit(45);
		}
		else if (data->exeprocess)
			;
		else
			rl_redisplay();
	}
}
