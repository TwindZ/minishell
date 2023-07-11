/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:50:01 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/10 19:59:23 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *arg)
{
	if (!strncmp(arg, "echo\0", 5)
		|| !strncmp(arg, "cd\0", 3)
		|| !strncmp(arg, "pwd\0", 4)
		|| !strncmp(arg, "export\0", 7)
		|| !strncmp(arg, "unset\0", 6)
		|| !strncmp(arg, "env\0", 4)
		|| !strncmp(arg, "exit\0", 5))
		return (1);
	return (0);
}

void	path_error(t_data *data, t_ltkn *temp, int err)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(temp->arg[0], 2);
	if(err)
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	else
		ft_putstr_fd(": no such file or directory\n", STDERR_FILENO);
	data->prevout = 127;
}

void	check_dir(t_data *data, t_ltkn *temp, char *arg)
{
	if(chdir(arg) == 0)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		if(temp->path)
		{
			free(temp->path);
			temp->path = NULL;
		}
		data->prevout = 126;
		temp->path = ft_strjoin(NULL, "*directory", 0);
	}
	else
	{
		data->pid.count++;
		temp->path = ft_strdup(arg);
	}
}

int	path_pre_check(t_data *data, char *arg, t_ltkn *temp)
{
	if (is_builtin(arg) == 1)
	{
		temp->path = ft_strjoin(temp->path, "*builtin", 0);
		return (1);
	}
	if (access(arg, X_OK) == 0)
	{
		check_dir(data, temp, arg);
		return (1);
	}
	else if(arg[0] == '.')
	{
		path_error(data, temp, 0);
		return (1);
	}
	return (0);
}


char	*create_path(char *prefix, char *sufix)
{
	char	*path;
	
	path = NULL;
	path = ft_strjoin(prefix, "/", 0);
	path = ft_strjoin(path, sufix, 1);
	if (access(path, X_OK) == 0)
		return (path);
	free(path);
	path = NULL;
	return (path);
}

void	find_path(t_data *data, t_ltkn *temp, char **paths, char **arg)
{
		int i;
		
		i = 0;
		while (paths[i])
		{
			if (temp->path)
				freenull(temp->path);
			temp->path = create_path(paths[i], arg[data->i]);
			if (temp->path)
			{
				data->pid.count++;
				break ;
			}
			i++;
		}
		ft_freeall(paths);
}

void	check_path(t_data *data, char **arg, t_ltkn *temp)
{
	char	**paths;
	char	*path_env;

	path_env = NULL;
	paths = NULL;
	if (path_pre_check(data, arg[data->i], temp))
		return ;
	path_env = getenvp(data, "PATH", 1);
	paths = ft_split(path_env, ':');
	if(path_env)
	{
		freenull(path_env);
	}
	if(paths)
		find_path(data, temp, paths, arg);
	if (!temp->path)
		path_error(data, temp, 1);
}
