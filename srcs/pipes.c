/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 08:55:55 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/07 11:13:35 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pipes(t_data *data)
{
	init_pipes(data);
	if (data->read[data->i] == '|')
	{
		make_temp(data);
		remake_line(data);
		data->i++;
	}
}

void	init_pipes(t_data *data)
{
	data->pipes.spaces = 1;
	data->pipes.i = 0;
	data->pipes.len = 0;
	data->pipes.temp = NULL;
}

void	make_temp(t_data *data)
{
	data->pipes.len = ft_strlen(data->line);
	if (data->line[data->i - 1] != '\t' && data->j > 0)
		data->pipes.spaces += 1;
	if (data->line[data->i + 1] != '\t')
		data->pipes.spaces += 1;
	data->pipes.temp = ft_calloc(data->pipes.len + data->pipes.spaces + 1,
		sizeof(char));
	if (!data->pipes.temp)
		mini_free(data);
	while (data->pipes.i <= data->pipes.len)
	{
		data->pipes.temp[data->pipes.i] = data->line[data->pipes.i];
		data->pipes.i++;
	}
	data->pipes.i = 0;
	free (data->line);
}

void	remake_line(t_data *data)
{
	data->pipes.len = ft_strlen(data->read) + ft_strlen(data->pipes.temp);
	data->line = ft_calloc((data->pipes.len + data->pipes.spaces),
		sizeof(char));
	if (!data->line)
		mini_free(data);
	while (data->pipes.temp[data->pipes.i])
	{
		data->line[data->pipes.i] = data->pipes.temp[data->pipes.i];
		data->pipes.i++;
	}
	if (data->read[data->i] == '|')
	{
		if (data->line[data->pipes.i - 1] != '\t' && data->j > 0)
			data->line[data->j++] = '\t';
		if (data->read[data->i] == '|')
			data->line[data->j++] = '|';
		if (data->line[data->pipes.i + 1] != '\t')
			data->line[data->j++] = '\t';
	}
	free (data->pipes.temp);
}
