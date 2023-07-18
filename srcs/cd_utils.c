/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:29:28 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/18 14:30:09 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
