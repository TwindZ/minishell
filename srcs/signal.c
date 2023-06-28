/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:23:51 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/27 17:44:55 by emlamoth         ###   ########.fr       */
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
	if(sig == SIGQUIT)
		ft_printf("no no no !!!!");//TODO enlever le message
	if(sig == SIGINT)
	{
		mini_reset(data);
		ft_putstr_fd("\n", 1);
		main_core(NULL);
	}
}