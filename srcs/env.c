/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 09:50:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/20 12:14:24 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	build_env(t_data *data, char **envp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	j = i;
	data->envp = ft_safe_calloc(i + 1, sizeof(char *), data);
	i = 0;
	while (i < j)
	{
		data->envp[i] = ft_safe_calloc(ft_strlen(envp[i]) + 1,
				sizeof(char), data);
		ft_strlcpy(data->envp[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
}

char	**env_cpy(char **envp, int exp, t_data *data)
{
	int		i;
	int		j;
	char	**enviro;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	j = i;
	enviro = ft_safe_calloc(i + 1 + exp, sizeof(char *), data);
	i = 0;
	while (i < j + exp)
	{
		enviro[i] = ft_safe_calloc(ft_strlen(envp[i]) + 1, sizeof(char), data);
		enviro[i] = ft_strdup(envp[i]);
		i++;
	}
	return (enviro);
}

char	*getenvp(t_data *data, char *var, int extract)
{
	init_env(data);
	data->env.len = ft_strlen(var);
	while (data->envp[data->env.i])
	{
		if ((ft_strncmp(data->envp[data->env.i], var, data->env.len) == 0)
			&& extract == 1)
		{
			find_var(data);
			return (data->env.result);
		}
		else if ((ft_strncmp(data->envp[data->env.i], var, data->env.len) == 0)
			&& extract == 0)
		{
			data->env.j = data->env.len + 1;
			data->env.result = ft_strjoin(NULL, "ok", 0);
			return (data->env.result);
		}
		data->env.i++;
	}
	return (0);
}

void	init_env(t_data *data)
{
	data->env.i = 0;
	data->env.j = 0;
	data->env.k = 0;
	data->env.len = 0;
	data->env.result = NULL;
}

void	find_var(t_data *data)
{
	data->env.j = data->env.len + 1;
	while (data->envp[data->env.i][data->env.j])
	{
		data->env.k++;
		data->env.j++;
	}
	data->env.result = ft_safe_calloc(data->env.k + 2, sizeof(char), data);
	data->env.j = data->env.len;
	data->env.k = 0;
	while (data->envp[data->env.i][data->env.j])
		data->env.result[data->env.k++] = data->envp[data->env.i]
		[data->env.j++];
}
