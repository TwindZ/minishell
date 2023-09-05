/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dshd_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:57:55 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/30 09:08:14 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Initialization for the heredoc environment variable resolver function*/
void	dshd_init(t_data *data)
{
	data->dshd.templine = NULL;
	data->dshd.vardata = NULL;
	data->dshd.var = NULL;
	data->dshd.varlen = 0;
	data->dshd.j = 0;
	data->dshd.i = 0;
	data->dshd.k = 0;
	data->dshd.save_j = 0;
}

/*This function checks if a dollar sign is present in the heredoc line.*/
int	dollar(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

/*This function checks for valid characters in environment variables.*/
int	var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}
