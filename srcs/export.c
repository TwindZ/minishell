/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:43:27 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/13 15:43:42 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_export(int fd, t_data *data, t_ltkn *temp)
{
	int	i;
	
	i = 1;
	while (temp->arg[i])
	{
		init_export(data);
		while (data->envp[data->exp.j])
			data->exp.j++;
		if (temp->arg[i] != NULL)
			add_to_env(data, temp, i);
		i++;
	}
	if (temp->arg[1] == NULL)
		print_env(fd, data);
}

void	add_to_env(t_data *data, t_ltkn *temp, int i)
{
	if (temp->arg[i][0] == '=' || ft_isdigit(temp->arg[i][0]) == 1)
		if (error_export(data, temp, i))
			return ;
	while (temp->arg[i][data->exp.i] != '=' && temp->arg[i][data->exp.i])
	{
		if (ft_isalnum(temp->arg[i][data->exp.i]) == 0
			&& temp->arg[i][0] != 95 && temp->arg[i][data->exp.i] != '=')
			if (error_export(data, temp, i))
				return ;
		data->exp.i++;
	}
	if (data->exp.i == (int)ft_strlen(temp->arg[i]))
		return ;
	data->exp.k = data->exp.i;
	data->exp.i = 0;
	while (ft_strncmp(temp->arg[i], data->envp[data->exp.i], data->exp.k))
		data->exp.i++;
	if (data->exp.i == data->exp.j)
		add_var(data, data->envp, temp, i);
	else if (data->exp.i != data->exp.j)
		modif_var(data, temp, i);
}

void	add_var(t_data *data, char **envp, t_ltkn *temp, int i)
{
	int		k;
	int		j;
	char	**new_env;

	k = 0;
	j = 0;
	while (envp[k])
		k++;
	j = k;
	new_env = ft_safe_calloc(k + 2, sizeof(char *), data);
	k = 0;
	while (k < j)
	{
		new_env[k] = ft_mini_strdup(envp[k], data);
		k++;
	}
	new_env[k] = ft_mini_strdup(temp->arg[i], data);
	ft_freeall(data->envp);
	data->envp = new_env;
}

void	modif_var(t_data *data, t_ltkn *temp, int i)
{
	data->exp.new_env = env_cpy(data->envp, 0, data);
	freenull(data->exp.new_env[data->exp.i]);
	data->exp.new_env[data->exp.i] = ft_mini_strdup(temp->arg[i], data);
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
