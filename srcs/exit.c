/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:24:58 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/13 10:13:16 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_exit(t_data *data, t_ltkn *temp)
{
	int child;
	
	child = 0;
	if(data->pid.count > 0)
		child = data->pid.pid[data->pid.index - 1];
	data->i = 0;
	data->j = 0;
	while (temp && temp->arg[data->j])
		data->j++;
	if (data->j > 2)
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", STDERR_FILENO);
		data->prevout = 1;
		return ;
	}
	if(data->pid.count)
	{
		kill(child, SIGQUIT);
		return ;
	}
	if (data->j == 2)
		exit_args(data, temp);
	else if (temp)
		exit_free(data);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(0);
}

void	exit_free(t_data *data)
{
	if(data->ltkn)
		free_list_ltkn(data->ltkn);
	if(data->read)
		freenull(data->read);
	if(data->line)
		freenull(data->line);
	ft_freeall(data->envp);
	freenull(data);
}

void	exit_args(t_data *data, t_ltkn *temp)
{
	int exitnum;

	exitnum = 0;
	if (temp->arg[1][0] == '-' || temp->arg[1][0] == '+')
		data->i++;
	while (ft_isdigit(temp->arg[1][data->i]) == 1)
		data->i++;
	if (data->i == (int)ft_strlen(temp->arg[1]))
	{
		exitnum = ft_atoi(temp->arg[1]);
		exit_free(data);
		exit(exitnum);
	}
	else 
	{
		ft_putstr_fd("Minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(temp->arg[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_free(data);
		exit(255);
	}
}
