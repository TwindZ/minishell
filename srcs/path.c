/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:50:01 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/14 14:31:35 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_path(t_data *data, char **arg, t_ltkn *temp)
{
	char	**paths;
	int i;
	
	i = 0;
	paths = ft_split(getenv("PATH"), ':');
	while (paths[i])
	{
		if(temp->path)
			free(temp->path);
		temp->path = ft_strjoin(paths[i], "/", 0);
		temp->path = ft_strjoin(temp->path, arg[data->i], 1);
		if (!access(temp->path, X_OK))
			break ;
		i++;
	}
	ft_freeall(paths);
	if(data->i == -1)
	{
		ft_printf("Minishell: %s: command not found\n", data->ltkn->arg[0]);
		
	}
		
}
