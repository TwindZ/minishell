/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:24:58 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/17 10:00:38 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	kill_child(t_data *data)
{
	int	child;

	child = 0;
	if (data->pid.count > 0)
		child = data->pid.pid[data->pid.index - 1];
	if (data->pid.count)
	{
		kill(child, SIGQUIT);
		data->exit_out = 1;
		if (data->j < 2)
			return (1);
	}
	return (0);
}

void	mini_exit(t_data *data, t_ltkn *temp)
{
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
	if (kill_child(data))
		return ;
	if (data->j == 2)
	{
		exit_args(data, temp);
		if (data->exit_out == 1)
			return ;
	}
	else if (temp)
		exit_free(data, 0);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(0);
}

void	exit_free(t_data *data, int ex)
{
	if (data->ltkn)
		free_list_ltkn(data->ltkn);
	if (data->read)
		free(data->read);
	if (data->line)
		free(data->line);
	ft_freeall(data->envp);
	free(data);
	if (ex)
		exit(1);
}

void	exit_args_err(t_data *data, t_ltkn *temp)
{
	ft_putstr_fd("Minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(temp->arg[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	if (data->exit_out)
		return ;
	exit_free(data, 0);
	exit(255);
}

void	exit_args(t_data *data, t_ltkn *temp)
{
	int	exitnum;

	exitnum = 0;
	if (temp->arg[1][0] == '-' || temp->arg[1][0] == '+')
		data->i++;
	while (ft_isdigit(temp->arg[1][data->i]) == 1)
		data->i++;
	if (data->i == (int)ft_strlen(temp->arg[1]))
	{
		exitnum = ft_atoi(temp->arg[1]);
		if (data->exit_out)
		{
			data->prevout = exitnum;
			return ;
		}
		exit_free(data, 0);
		exit(exitnum);
	}
	else 
		exit_args_err(data, temp);
}
