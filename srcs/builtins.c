/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:35:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/08/27 10:08:34 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*This function returns the current working directory.*/
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

/*This function returns the environment of minishell.*/
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

/*This function removes an environment variable from the minishell by copying
the environment to a new one without the variable to unset.*/
void	mini_unset(t_data *data, t_ltkn *temp)
{
	int	i;

	i = 1;
	data->flag = 0;
	while (temp->arg[i])
	{
		data->i = 0;
		data->j = 0;
		data->unset.to_find = NULL;
		while (data->envp[data->i])
			data->i++;
		data->unset.new_env = ft_safe_calloc(data->i + 1, sizeof(char *), data);
		data->i = 0;
		data->unset.to_find = ft_mini_strjoin(temp->arg[i], "=", 0, data);
		unset_adjust(data, temp, i);
		if (data->unset.new_env[data->j] == NULL && data->flag == 0)
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

/*This function is used by mini_unset to recopy the environment without the
environment variable to remove.*/
void	unset_adjust(t_data *data, t_ltkn *temp, int i)
{
	while (data->envp[data->i])
	{
		if (temp->arg[i] == NULL || (ft_isalpha(temp->arg[i][0]) == 0
			&& temp->arg[i][0] != 95 && temp->arg[i][0] == 47))
		{
			data->flag = 1;
			unset_error(data, temp, i);
			return ;
		}
		else if (ft_strncmp(data->unset.to_find, data->envp[data->i],
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

/*Error handler for mini_unset.*/
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
