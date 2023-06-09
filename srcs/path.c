/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:50:01 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/09 09:45:52 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_path(t_data *data)
{
	char	*path;

	path = NULL;
	data->i = 0;
	data->j = 0;
	data->path = ft_split(getenv("PATH"), ':');
	
	while (data->path[data->j])
	{
		path = ft_strjoin(data->path[data->j], "/", 0);
		path = ft_strjoin(path, data->ltkn->arg[0], 1);//temporaire
		data->i = access(path, X_OK);
		if (data->i == 0)
		{
			make_list_lcmd(data, path);
			break;
		}
		data->j++;
		free (path);
	}
	if(data->i == -1)
		ft_printf("Minishell: %s: command not found\n", data->ltkn->arg[0]);
}
