/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:47:35 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/22 14:00:15 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replace_meta(t_data *data)
{
	if (data->read[data->i] == '|' || data->read[data->i] == '<'
		|| data->read[data->i] == '>')
	{
		if (data->read[data->i] == '|')
			data->line[data->j++] = '?';
		if (data->read[data->i] == '<')
			data->line[data->j++] = '%';
		if (data->read[data->i] == '>')
			data->line[data->j++] = '@';
		data->i++;
	}
}
//TODO changer les caractères pour du ascii ou du non imprimable.

void	meta_replace(t_data *data)
{
	if (data->read[data->i] == '?' || data->read[data->i] == '%'
		|| data->read[data->i] == '@')
	{
		if (data->read[data->i] == '?')
			data->line[data->j++] = '|';
		if (data->read[data->i] == '%')
			data->line[data->j++] = '<';
		if (data->read[data->i] == '@')
			data->line[data->j++] = '>';
		data->i++;
	}
}
