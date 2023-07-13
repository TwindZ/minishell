/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:24:58 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/13 15:10:58 by emlamoth         ###   ########.fr       */
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
		exit_free(data, 0);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(0);
}

void	exit_free(t_data *data, int ex)
{
	if(data->ltkn)
		free_list_ltkn(data->ltkn);
	if(data->read)
		free(data->read);
	if(data->line)
		free(data->line);
	ft_freeall(data->envp);
	free(data);
	if(ex)
		exit(1);
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
		exit_free(data, 0);
		exit(exitnum);
	}
	else 
	{
		ft_putstr_fd("Minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(temp->arg[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_free(data, 0);
		exit(255);
	}
}

void *ft_mini_strdup(const char *s, t_data *data)
{
	void	*str;

	str = NULL;
	str = ft_safe_calloc(ft_strlen(s) + 1, sizeof(char), data);
	ft_memcpy(str, s, ft_strlen(s) + 1);
	return (str);
}
