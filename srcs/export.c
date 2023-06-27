/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:43:27 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/27 14:51:50 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_export(t_data *data, t_ltkn *temp)
{
	init_export(data);
	while (data->envp[data->exp.j])
		data->exp.j++;
	if (temp->arg[1] != NULL)
		add_to_env(data, temp);
	if (temp->arg[1] == NULL)
		print_env(data);
}
	// TODO changer les messages d'erreurs avec stderr ou perror

void	add_to_env(t_data *data, t_ltkn *temp)
{
	while (temp->arg[1][data->exp.i] != '=')
		data->exp.i++;
	data->exp.k = data->exp.i;
	data->exp.i = 0;
	while (ft_strncmp(temp->arg[1], data->envp[data->exp.i], data->exp.k))
		data->exp.i++;
	if (data->exp.i == data->exp.j)
		add_var(data, data->envp, temp);
	else if (data->exp.i != data->exp.j)
	{
		data->exp.new_env = env_cpy(data->envp, 0);
		free (data->exp.new_env[data->exp.i]);
		data->exp.new_env[data->exp.i] = NULL;
		data->exp.new_env[data->exp.i] = ft_calloc(ft_strlen(temp->arg[1]) + 1, sizeof(char));
		ft_strlcpy(data->exp.new_env[data->exp.i], temp->arg[1], ft_strlen(temp->arg[1]) + 1);
		ft_freeall(data->envp);
		data->envp = NULL;
		data->envp = env_cpy(data->exp.new_env, 0);
		ft_freeall(data->exp.new_env);
	}
}

void	add_to_env_test(t_data *data, t_ltkn *temp)
{
	while (temp->arg[1][data->exp.i] != '=')
		data->exp.i++;
	data->exp.k = data->exp.i;
	data->exp.i = 0;
	
	while (ft_strncmp(temp->arg[1], data->envp[data->exp.i], data->exp.k))
		data->exp.i++;
	if (data->exp.i == data->exp.j)
	{
		data->exp.new_env = env_cpy(data->envp, 1);
		data->exp.new_env[data->exp.j]
			= ft_calloc(ft_strlen(temp->arg[1]), sizeof(char));
		data->exp.new_env[data->exp.j] = temp->arg[1];
		ft_printf("%s\n", data->exp.new_env[data->exp.j - 2]);
		ft_freeall(data->envp);
		data->envp = data->exp.new_env;
	}
	else if (data->exp.i != data->exp.j)
	{
		data->exp.new_env = env_cpy(data->envp, 0);
		free (data->exp.new_env[data->exp.i]);
		// data->exp.new_env[data->exp.i]
		// 	= ft_calloc(ft_strlen(temp->arg[1]), sizeof(char));
		data->exp.new_env[data->exp.i] = temp->arg[1];
		ft_freeall(data->envp);
		data->envp = data->exp.new_env;
	}
}

void	print_env(t_data *data)
{
	data->exp.temp_env = env_cpy(data->envp, 0);
	while (data->exp.i < data->exp.j - 1)
	{
		data->exp.k = 0;
		while (data->exp.k < data->exp.j - 1)
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
		data->exp.i++;
	}
	data->exp.i = 0;
	while (data->exp.temp_env[data->exp.i])
		ft_printf("declare -x %s\n", data->exp.temp_env[data->exp.i++]);
	free (data->exp.temp_env);
	data->exp.swap = NULL;
}

void	init_export(t_data *data)
{
	data->exp.i = 0;
	data->exp.j = 0;
	data->exp.k = 0;
	data->exp.new_env = NULL;
	data->exp.temp_env = NULL;
	data->exp.swap = NULL;
}
