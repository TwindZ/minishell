/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:01:39 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/13 15:36:17 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_export(t_data *data)
{
	data->exp.i = 0;
	data->exp.j = 0;
	data->exp.k = 0;
	data->exp.new_env = NULL;
	data->exp.temp_env = NULL;
	data->exp.swap = NULL;
}

int	error_export(t_data *data, t_ltkn *temp, int arg)
{
	ft_putstr_fd("Minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(temp->arg[arg], STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	data->prevout = 1;
	return (1);
}

void	export_sort(t_data *data)
{
	if (ft_strncmp(data->exp.temp_env[data->exp.k],
			data->exp.temp_env[data->exp.k + 1],
			ft_strlen(data->exp.temp_env[data->exp.k])) > 0)
	{
		data->exp.swap = data->exp.temp_env[data->exp.k];
		data->exp.temp_env[data->exp.k]
			= data->exp.temp_env[data->exp.k + 1];
		data->exp.temp_env[data->exp.k + 1] = data->exp.swap;
	}
	data->exp.k++;
}
