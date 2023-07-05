/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:19:05 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/29 15:04:10 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_cd(t_data *data, t_ltkn *temp)
{
	char	*home;

	data->i = 0;
	home = NULL;
	home = getenvp(data, "HOME=", 1);
	if (!home)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", STDERR_FILENO);
		data->prevout = 1;
		return ;
	}
	while (temp->arg[data->i])
		data->i++;
	change_dir(data, temp, home);
	freenull(home);
}

void	change_dir(t_data *data, t_ltkn *temp, char *home)
{
	int	result;

	result = 0;
	if (data->i == 2)
	{
		data->i = 1;
		result = chdir(temp->arg[data->i]);
		if (result != 0)
		{
			ft_putstr_fd("Minishell: cd: ", STDERR_FILENO);
			ft_putstr_fd(temp->arg[data->i], STDERR_FILENO);
			ft_putstr_fd(": no such file or directory\n", STDERR_FILENO);
		}
		return ;
	}
	else if (data->i == 1)
	{
		result = chdir(home);
		if (result != 0)
			ft_putstr_fd("Minishell: cd: cant't find HOME directory\n",
				STDERR_FILENO);
		data->prevout = 1;
		return ;
	}
	else if (data->i > 2)
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", STDERR_FILENO);
		data->prevout = 1;
		return ;
	}
}
