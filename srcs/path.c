/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:50:01 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/29 13:40:54 by fbouchar         ###   ########.fr       */
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

int	path_pre_check(char *arg, t_ltkn *temp)
{
	if (is_builtin(arg) == 1)
	{
		temp->path = ft_strjoin(temp->path, "*builtin", 0);
		return (1);
	}
	if (access(arg, X_OK) == 0)
	{
		if(chdir(arg) == 0)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": is a directory\n", 2);
			temp->path = ft_strjoin(NULL, "directory",0);
			return (0);
		}
		else
		temp->path = arg;
		return (1);
	}
	return (0);
}

void	path_error(t_ltkn *temp)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(temp->arg[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

char	*find_path(char *prefix, char *sufix)
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

void	check_path(t_data *data, char **arg, t_ltkn *temp)
{
	char	**paths;
	char	*path_env;
	int		i;

	i = 0;
	path_env = NULL;
	paths = NULL;
	if (path_pre_check(arg[data->i], temp))
		return ;
	path_env = getenvp(data, "PATH", 1);
	paths = ft_split(path_env, ':');
	if(path_env)
	{
		free(path_env);
		path_env = NULL;
	}
	if(paths)
	{
		while (paths[i])
		{
			if (ft_strncmp(temp->path, "directory", ft_strlen("directory")) == 0)
				return ;
			if (temp->path)
			{
				free(temp->path);
				temp->path = NULL;
			}
			temp->path = find_path(paths[i], arg[data->i]);
			if (temp->path)
				break ;
			i++;
		}
		ft_freeall(paths);
	}
	if (!temp->path)
		path_error(temp);
}
