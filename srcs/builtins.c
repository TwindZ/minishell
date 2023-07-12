/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:35:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/12 15:59:46 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_pwd(int fd, t_data *data)
{
	char	buffer[PATH_MAX];
	char	*cwd;
	
	cwd = getcwd(buffer, sizeof(buffer));
	if(!cwd)
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
	data->i = 0;
	data->j = 0;
	data->unset.to_find = NULL;
	while (data->envp[data->i])
		data->i++;
	data->unset.new_env = ft_safe_calloc(data->i + 1, sizeof(char *), data);
	data->i = 0;
	data->unset.to_find = ft_strjoin(temp->arg[1], "=", 0);
	unset_adjust(data, temp);
	if (data->unset.new_env[data->j] == NULL)
	{
		ft_freeall(data->envp);
		data->envp = env_cpy(data->unset.new_env, 0, data);
	}
	data->prevout = 0;
	ft_freeall(data->unset.new_env);
	freenull(data->unset.to_find);
}

void	unset_adjust(t_data *data, t_ltkn *temp)
{
	while (data->envp[data->i])
	{
		if (temp->arg[1] == NULL || (ft_isalpha(temp->arg[1][0]) == 0
			&& temp->arg[1][0] != 95 && temp->arg[1][0] == 47))
		{
			unset_error(data, temp);
			return ;
		}
		if (ft_strncmp(data->unset.to_find, data->envp[data->i],
				ft_strlen(data->unset.to_find)) == 0)
			;
		else
		{
			data->unset.new_env[data->j] = ft_strdup(data->envp[data->i]);
			data->j++;
		}
		data->i++;
	}
}

void	unset_error(t_data *data, t_ltkn *temp)
{
	ft_putstr_fd("Minishell: unset: `", STDERR_FILENO);
	if (temp->arg[1] == NULL)
		ft_putstr_fd("", STDERR_FILENO);
	else
		ft_putstr_fd(temp->arg[1], STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	data->prevout = 1;
}
