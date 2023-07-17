/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:17:06 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/17 09:49:51 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_echo(int fd, t_ltkn *temp, t_data *data)
{
	data->i = 1;
	data->flag = 0;
	if (temp->arg[1] == NULL)
	{
		ft_putstr_fd("\n", fd);
		return ;
	}
	if (ft_strncmp(temp->arg[1], "-n\0", 3) == 0 && temp->arg[2] == NULL)
	{
		return ;
	}
	while (temp->arg[data->i])
	{
		echo_print(fd, temp, data);
	}
	if (ft_strncmp(temp->arg[1], "-n\0", 3))
		ft_putstr_fd("\n", fd);
	data->prevout = 0;
}

void	echo_print(int fd, t_ltkn *temp, t_data *data)
{
	while (ft_strncmp(temp->arg[data->i], "-n\0", 3) == 0
		&& temp->arg[data->i + 1] != NULL && data->flag == 0)
		data->i++;
	if (ft_strncmp(temp->arg[data->i], "-n\0", 3) == 0 && data->flag == 1)
	{
		meta_replace(temp);
		ft_putstr_fd(temp->arg[data->i], fd);
		if (ft_strncmp(temp->arg[data->i + 1], "-n\0", 3) == 0)
			data->flag = 1;
		else 
			data->flag = 0;
	}
	else if (ft_strncmp(temp->arg[data->i], "-n\0", 3) && data->flag == 0)
	{
		ft_putstr_fd(temp->arg[data->i], fd);
		if (ft_strncmp(temp->arg[data->i + 1], "-n\0", 3))
			data->flag = 0;
		else
			data->flag = 1;
	}
	data->i++;
	if (temp->arg[data->i] != NULL)
		ft_putstr_fd(" ", fd);
}
