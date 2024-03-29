/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:50:01 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/27 17:56:40 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*These functions are used to determine if an argument is a valid command by 
searching its path in the environment variable PATH.*/

/* These functions are used to check if the argument is a directory. */
void	check_dir(t_data *data, t_ltkn *temp, char *arg)
{
	if (chdir(arg) == 0)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		if (temp->path)
		{
			free(temp->path);
			temp->path = NULL;
		}
		data->prevout = 126;
		temp->path = ft_mini_strjoin(NULL, "*directory", 0, data);
	}
	else
	{
		data->pid.count++;
		temp->path = ft_mini_strdup(arg, data);
	}
}

/* These functions are used to check if the argument is a built-in command
or if it is an absolute file path. */
int	path_pre_check(t_data *data, char *arg, t_ltkn *temp)
{
	if (is_builtin(arg) == 1)
	{
		temp->path = ft_mini_strjoin(temp->path, "*builtin", 0, data);
		return (1);
	}
	if (access(arg, X_OK) == 0)
	{
		check_dir(data, temp, arg);
		return (1);
	}
	else if (arg[0] == '.')
	{
		path_error(data, temp, 0);
		return (1);
	}
	return (0);
}

/*The two next functions are used to create the complete path, test the access,
and if the access works, the path is stored in the command node.*/
char	*create_path(char *prefix, char *sufix, t_data *data)
{
	char	*path;

	path = NULL;
	path = ft_mini_strjoin(prefix, "/", 0, data);
	path = ft_mini_strjoin(path, sufix, 1, data);
	if (access(path, X_OK) == 0)
		return (path);
	free(path);
	path = NULL;
	return (path);
}

void	find_path(t_data *data, t_ltkn *temp, char **paths, char **arg)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (temp->path)
			free(temp->path);
		temp->path = create_path(paths[i], arg[data->i], data);
		if (temp->path)
		{
			data->pid.count++;
			break ;
		}
		i++;
	}
	ft_freeall(paths);
}

/*This is the main function for the path parameter of the node;
the data of the environment variable PATH is split here.*/
void	check_path(t_data *data, char **arg, t_ltkn *temp)
{
	char	**paths;
	char	*path_env;

	path_env = NULL;
	paths = NULL;
	if (path_pre_check(data, arg[data->i], temp))
		return ;
	path_env = getenvp(data, "PATH=", 1);
	paths = ft_split(path_env, ':');
	if (path_env)
	{
		free(path_env);
	}
	if (paths)
		find_path(data, temp, paths, arg);
	if (!temp->path)
		path_error(data, temp, 1);
}
