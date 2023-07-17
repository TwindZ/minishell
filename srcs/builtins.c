/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:35:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/17 09:37:30 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_pwd(int fd, t_data *data)
{
	char	buffer[PATH_MAX];
	char	*cwd;

	cwd = getcwd(buffer, sizeof(buffer));
	if (!cwd)
		cwd = data->lastwd;
	ft_putstr_fd(cwd, fd);
	ft_putstr_fd("\n", fd);
	data->prevout = 0;
}

void	mini_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		ft_putstr_fd(data->envp[i], data->fd.cmd_out);
		ft_putstr_fd("\n", data->fd.cmd_out);
		i++;
	}
	data->prevout = 0;
}

void	mini_unset(t_data *data, t_ltkn *temp)
{
	int	i;

	i = 1;
	while (temp->arg[i])
	{
		data->i = 0;
		data->j = 0;
		data->unset.to_find = NULL;
		while (data->envp[data->i])
			data->i++;
		data->unset.new_env = ft_safe_calloc(data->i + 1, sizeof(char *), data);
		data->i = 0;
		data->unset.to_find = ft_strjoin(temp->arg[i], "=", 0);
		unset_adjust(data, temp, i);
		if (data->unset.new_env[data->j] == NULL)
		{
			ft_freeall(data->envp);
			data->envp = env_cpy(data->unset.new_env, 0, data);
		}
		data->prevout = 0;
		ft_freeall(data->unset.new_env);
		free(data->unset.to_find);
		i++;
	}
}

void	unset_adjust(t_data *data, t_ltkn *temp, int i)
{
	while (data->envp[data->i])
	{
		if (temp->arg[i] == NULL || (ft_isalpha(temp->arg[i][0]) == 0
			&& temp->arg[i][0] != 95 && temp->arg[i][0] == 47))
		{
			unset_error(data, temp, i);
			return ;
		}
		if (ft_strncmp(data->unset.to_find, data->envp[data->i],
				ft_strlen(data->unset.to_find)) == 0)
			;
		else
		{
			data->unset.new_env[data->j]
				= ft_mini_strdup(data->envp[data->i], data);
			data->j++;
		}
		data->i++;
	}
}

void	unset_error(t_data *data, t_ltkn *temp, int i)
{
	ft_putstr_fd("Minishell: unset: `", STDERR_FILENO);
	if (temp->arg[i] == NULL)
		ft_putstr_fd("", STDERR_FILENO);
	else
		ft_putstr_fd(temp->arg[i], STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	data->prevout = 1;
}
