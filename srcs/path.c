/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:50:01 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/19 03:37:03 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_path(t_data *data, char **arg, t_ltkn *temp)
{
	char	**paths;
	int i;
	int acc;
	
	acc = 0;
	i = 0;
	if(access(arg[data->i], X_OK) == 0)//TODO dois fonctionner avec un chemin absolut
	{
		temp->path = arg[data->i];
		return ;
	}
	paths = ft_split(getenv("PATH"), ':');
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
		temp->path = NULL;
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(temp->arg[0], 2);
		ft_putstr_fd(": command not found\n", 2) ;
	}
}
