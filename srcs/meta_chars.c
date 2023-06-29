/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 08:55:55 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/07 11:20:26 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	meta_chars(t_data *data, char meta)
{
	init_meta(data);
	if (data->read[data->i] == meta)
	{
		make_temp(data);
		remake_line(data, meta);
		data->i++;
	}
}

void	init_meta(t_data *data)
{
	data->meta.spaces = 1;
	data->meta.i = 0;
	data->meta.len = 0;
	data->meta.temp = NULL;
}

void	make_temp(t_data *data)
{
	data->meta.len = ft_strlen(data->line);
	if (data->line[data->i - 1] != '\t' && data->j > 0)
		data->meta.spaces += 1;
	if (data->line[data->i + 1] != '\t')
		data->meta.spaces += 1;
	data->meta.temp = ft_safe_calloc(data->meta.len + data->meta.spaces + 1,
			sizeof(char), data);
	while (data->meta.i <= data->meta.len)
	{
		data->meta.temp[data->meta.i] = data->line[data->meta.i];
		data->meta.i++;
	}
	data->meta.i = 0;
	free (data->line);
	data->line = NULL;
}

void	remake_line(t_data *data, char meta)
{
	data->meta.len = ft_strlen(data->read) + ft_strlen(data->meta.temp);
	data->line = ft_safe_calloc((data->meta.len + data->meta.spaces),
			sizeof(char), data);
	while (data->meta.temp[data->meta.i])
	{
		data->line[data->meta.i] = data->meta.temp[data->meta.i];
		data->meta.i++;
	}
	place_tab(data, meta);
	free (data->meta.temp);
	data->meta.temp = NULL;
}

void	place_tab(t_data *data, char meta)
{
	if (data->read[data->i] == meta)
	{
		if (data->line[data->meta.i - 1] != '\t' && data->j > 0)
			data->line[data->j++] = '\t';
		if (data->read[data->i] == meta)
			data->line[data->j++] = meta;
		if (data->read[data->i + 1] == meta)
		{
			data->line[data->j++] = meta;
			data->meta.i++;
			data->i++;
		}
		if (data->line[data->meta.i + 1] != '\t')
			data->line[data->j++] = '\t';
	}
}
