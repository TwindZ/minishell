/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:46:58 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/08 11:12:49 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dollar_sign(t_data *data)
{
	init_dollar(data);
	if (data->read[data->i] == '$')
	{
		make_tocheck(data);
		data->dolsign.towrite = getenv(data->dolsign.tocheck);
		if (data->dolsign.towrite != NULL)
			adjust_line(data);
		free(data->dolsign.tocheck);
	}
}

void	init_dollar(t_data *data)
{
	data->dolsign.start = 0;
	data->dolsign.end = 0;
	data->dolsign.len = 0;
	data->dolsign.idx = 0;
	data->dolsign.tocheck = NULL;
	data->dolsign.towrite = NULL;
}

void	make_tocheck(t_data *data)
{
	data->i++;
	data->dolsign.start = data->i;
	while ((data->read[data->i] >= 65 && data->read[data->i] <= 90)
		|| (data->read[data->i] >= 97 && data->read[data->i] <= 121)
		|| (data->read[data->i] >= 48 && data->read[data->i] <= 57)
		|| data->read[data->i] == '_' )
		data->i++;
	data->dolsign.end = data->i;
	data->dolsign.len = data->dolsign.end - data->dolsign.start;
	data->dolsign.tocheck = malloc(sizeof(char) * data->dolsign.len + 1);
	if (!data->dolsign.tocheck)
		mini_free(data);
	while (data->dolsign.start < data->dolsign.end)
	{
		data->dolsign.tocheck[data->dolsign.idx]
			= data->read[data->dolsign.start++];
		if (data->dolsign.tocheck[0] >= 48 && data->dolsign.tocheck[0] <= 57)
		{
			data->i = data->dolsign.start;
			break ;
		}
		data->dolsign.idx++;
	}
	data->dolsign.tocheck[data->dolsign.idx] = '\0';
}

void	adjust_line(t_data *data)
{
	init_adjust(data);
	while (data->dolsign.i < data->dolsign.linelen
		|| data->line[data->dolsign.i])
	{
		data->linetemp[data->dolsign.i] = data->line[data->dolsign.i];
		data->dolsign.i++;
	}
	data->dolsign.i = 0;
	free (data->line);
	data->line = ft_calloc((data->dolsign.linelen
				+ data->dolsign.towritelen + 2), sizeof(char));
	if (!data->line)
		mini_free(data);
	while (data->linetemp[data->dolsign.i])
	{
		data->line[data->dolsign.i] = data->linetemp[data->dolsign.i];
		data->dolsign.i++;
	}
	data->dolsign.i = 0;
	while (data->dolsign.towritelen-- != 0)
		data->line[data->j++] = data->dolsign.towrite[data->dolsign.i++];
	if (data->linetemp != NULL)
		free (data->linetemp);
}

void	init_adjust(t_data *data)
{
	data->dolsign.i = 0;
	data->dolsign.linelen = ft_strlen(data->line);
	data->dolsign.towritelen = ft_strlen(data->dolsign.towrite);
	data->linetemp = NULL;
	data->linetemp = ft_calloc(data->dolsign.linelen + 1, sizeof(char));
}
