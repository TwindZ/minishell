/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:50:01 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/21 13:08:52 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *arg)
{
	if(!strncmp(arg, "echo\0", 5)
		|| !strncmp(arg, "cd\0", 3)
		|| !strncmp(arg, "pwd\0", 4)
		|| !strncmp(arg, "export\0", 7)
		|| !strncmp(arg, "unset\0", 6)
		|| !strncmp(arg, "env\0", 4)
		|| !strncmp(arg, "exit\0", 5))
		return (1);
	return (0);
}

void	check_path(t_data *data, char **arg, t_ltkn *temp)
{
	char	**paths;
	char	*path_env;
	int i;
	int acc;
	
	acc = 0;
	i = 0;
	if(is_builtin(arg[data->i]) == 1)
	{
		temp->path = ft_strjoin(temp->path, "*builtin", 0);
		return;
	}
	if(access(arg[data->i], X_OK) == 0)//TODO dois fonctionner avec un chemin absolut
	{
		temp->path = arg[data->i];
		return ;
	}
	path_env = getenvp(data, "PATH", 1);
	paths = ft_split(path_env, ':');
	free(path_env)
	while (paths[i])
	{
		if(temp->path)
			free(temp->path);
		temp->path = ft_strjoin(paths[i], "/", 0);
		temp->path = ft_strjoin(temp->path, arg[data->i], 1);
		acc = access(temp->path, X_OK);
		if (acc == 0)
			break ;
		i++;
	}
	ft_freeall(paths);
	if(acc == -1)
	{
		free(temp->path);
		temp->path = ft_calloc(1, sizeof(char *));
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(temp->arg[0], 2);
		ft_putstr_fd(": command not found\n", 2) ;
	}
}
