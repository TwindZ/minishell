/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_ltkn_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:25:23 by emman             #+#    #+#             */
/*   Updated: 2023/06/21 22:26:30 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_meta(t_data *data, char **arg)
{
	if(!ft_strncmp(arg[data->i], "<<\0", 3)
		|| !ft_strncmp(arg[data->i], "<\0", 2)
		|| !ft_strncmp(arg[data->i], ">>\0", 3)
		|| !ft_strncmp(arg[data->i], ">\0", 2))
		return(1);
	return (0);
}

void build_cmd_param(t_data *data, char **arg, t_ltkn *temp)
{
	if(strncmp(arg[data->i], "|\0", 2) == 0)
	{
		temp->front_pipe = 1;
		data->j = 0;
		return ;
	}	
	else if(is_meta(data, arg))
		set_meta(data, arg);
	else
		temp->arg[data->j++] = arg[data->i];
}