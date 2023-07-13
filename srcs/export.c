/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:43:27 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/12 14:47:32 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_export(int fd, t_data *data, t_ltkn *temp)
{
	init_export(data);
	while (data->envp[data->exp.j])
		data->exp.j++;
	if (temp->arg[1] != NULL)
		add_to_env(data, temp);
	if (temp->arg[1] == NULL)
		print_env(fd, data);
}

void	add_to_env(t_data *data, t_ltkn *temp)
{
	if (temp->arg[1][0] == '=' || ft_isdigit(temp->arg[1][0]) == 1)
		error_export(data, temp, 1);
	if (temp->arg[2] != NULL && temp->arg[2][0] == '=')
		error_export(data, temp, 2);
	while (temp->arg[1][data->exp.i] != '=' && temp->arg[1][data->exp.i])
	{
		if (ft_isalnum(temp->arg[1][data->exp.i]) == 0
			&& temp->arg[1][0] != 95 && temp->arg[1][data->exp.i] != '=')
			error_export(data, temp, 1);
		data->exp.i++;
	}
	if (data->exp.i == (int)ft_strlen(temp->arg[1]))
		return ;
	data->exp.k = data->exp.i;
	data->exp.i = 0;
	while (ft_strncmp(temp->arg[1], data->envp[data->exp.i], data->exp.k))
		data->exp.i++;
	if (data->exp.i == data->exp.j)
		add_var(data, data->envp, temp);
	else if (data->exp.i != data->exp.j)
		modif_var(data, temp);
}

void	add_var(t_data *data, char **envp, t_ltkn *temp)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	j = i;
	new_env = ft_safe_calloc(i + 2, sizeof(char *), data);
	i = 0;
	while (i < j)
	{
		new_env[i] = ft_safe_calloc(ft_strlen(envp[i]) + 1,
				sizeof(char), data);
		ft_strlcpy(new_env[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	new_env[i] = ft_safe_calloc(ft_strlen(temp->arg[1]) + 1,
			sizeof(char), data);
	ft_strlcpy(new_env[i], temp->arg[1], ft_strlen(temp->arg[1]) + 1);
	ft_freeall(data->envp);
	data->envp = new_env;
}

void	modif_var(t_data *data, t_ltkn *temp)
{
	data->exp.new_env = env_cpy(data->envp, 0, data);
	freenull(data->exp.new_env[data->exp.i]);
	data->exp.new_env[data->exp.i] = ft_safe_calloc(
			ft_strlen(temp->arg[1]) + 1, sizeof(char), data);
	ft_strlcpy(data->exp.new_env[data->exp.i], temp->arg[1],
		ft_strlen(temp->arg[1]) + 1);
	ft_freeall(data->envp);
	data->envp = env_cpy(data->exp.new_env, 0, data);
	data->prevout = 0;
	ft_freeall(data->exp.new_env);
}

void	print_env(int fd, t_data *data)
{
	data->exp.temp_env = env_cpy(data->envp, 0, data);
	while (data->exp.i < data->exp.j - 1)
	{
		data->exp.k = 0;
		while (data->exp.k < data->exp.j - 1)
		{
			export_sort(data);
		}
		data->exp.i++;
	}
	data->exp.i = 0;
	while (data->exp.temp_env[data->exp.i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(data->exp.temp_env[data->exp.i++], fd);
		ft_putstr_fd("\n", fd);
		data->prevout = 0;
	}
	ft_freeall(data->exp.temp_env);
	data->exp.swap = NULL;
}
