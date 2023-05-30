/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:50:01 by fbouchar          #+#    #+#             */
/*   Updated: 2023/05/30 15:36:29 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_path(t_data *data)
{
	char	*name;

	name = NULL;
	data->i = 0;
	data->j = 0;
	data->path = ft_split(getenv("PATH"), ':');
	while (data->path[data->j])
	{
		name = ft_strjoin(data->path[data->j], "/", 0);
		name = ft_strjoin(name, data->ltkn->token, 1);
		ft_printf("%s\n", name);
		data->i = access(name, X_OK);
		// ft_printf("%i", data->i);
		if (data->i == 0)
		{
			data->lcmd->cmdpath = name;
			break;
		}
		data->j++;
		free (name);
	}
}