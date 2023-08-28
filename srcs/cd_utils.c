/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:29:28 by fbouchar          #+#    #+#             */
/*   Updated: 2023/08/27 10:11:58 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*These functions are used to handle errors from the mini_cd function.*/
void	error_directory(t_data *data, t_ltkn *temp)
{
	ft_putstr_fd("Minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(temp->arg[data->i], STDERR_FILENO);
	ft_putstr_fd(": no such file or directory\n", STDERR_FILENO);
	data->prevout = 1;
}

void	error_arguments(t_data *data)
{
	ft_putstr_fd("Minishell: cd: too many arguments\n", STDERR_FILENO);
	data->prevout = 1;
	return ;
}
