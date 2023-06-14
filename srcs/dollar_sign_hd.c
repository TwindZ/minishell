/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_hd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:43:01 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/14 14:58:04 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dollar_sign_hd(t_data *data)
{
	init_dollar_hd(data);
	if (data->hd.data[data->hd.i] == '$')
	{
		make_tocheck_hd(data);
		data->dshd.towrite = getenv(data->dshd.tocheck);
		if (data->dshd.towrite != NULL)
			adjust_line_hd(data);
		free(data->dshd.tocheck);
	}
}

void	init_dollar_hd(t_data *data)
{
	data->dshd.start = 0;
	data->dshd.end = 0;
	data->dshd.len = 0;
	data->dshd.idx = 0;
	data->dshd.tocheck = NULL;
	data->dshd.towrite = NULL;
}

void	make_tocheck_hd(t_data *data)
{
	data->dshd.start2 = data->hd.i;
	data->hd.i++;
	data->dshd.start = data->hd.i;
	while ((data->hd.data[data->hd.i] >= 65 && data->hd.data[data->hd.i] <= 90)
		|| (data->hd.data[data->hd.i] >= 97 && data->hd.data[data->hd.i] <= 121)
		|| (data->hd.data[data->hd.i] >= 48 && data->hd.data[data->hd.i] <= 57)
		|| data->hd.data[data->hd.i] == '_' )
		data->hd.i++;
	data->dshd.end = data->hd.i;
	data->dshd.len = data->dshd.end - data->dshd.start;
	data->dshd.tocheck = malloc(sizeof(char) * data->dshd.len + 1);
	if (!data->dshd.tocheck)
		mini_free(data);
	while (data->dshd.start < data->dshd.end)
	{
		data->dshd.tocheck[data->dshd.idx]
			= data->hd.data[data->dshd.start++];
		if (data->dshd.tocheck[0] >= 48 && data->dshd.tocheck[0] <= 57)
		{
			data->hd.i = data->dshd.start;
			break ;
		}
		data->dshd.idx++;
	}
	data->dshd.tocheck[data->dshd.idx] = '\0';
}

void	adjust_line_hd(t_data *data)
{
	init_adjust_hd(data);
	while (data->dshd.i < data->dshd.linelen
		|| data->hd.data[data->dshd.i])
	{
		data->linetemp[data->dshd.i] = data->hd.data[data->dshd.i];
		data->dshd.i++;
	}
	data->dshd.i = 0;
	free (data->hd.data);
	data->hd.data = ft_calloc((data->dshd.linelen
				+ data->dshd.towritelen
				+ ft_strlen(data->readhd) + 2), sizeof(char));
	if (!data->hd.data)
		mini_free(data);
	while (data->linetemp[data->dshd.i])
	{
		data->hd.data[data->dshd.i] = data->linetemp[data->dshd.i];
		data->dshd.i++;
	}
	data->dshd.i = 0;
	while (data->dshd.towritelen-- != 0)
		data->hd.data[data->dshd.start2++] = data->dshd.towrite[data->dshd.i++];
	if (data->linetemp != NULL)
		free (data->linetemp);
}

void	init_adjust_hd(t_data *data)
{
	data->dshd.i = 0;
	data->dshd.linelen = ft_strlen(data->hd.data);
	data->dshd.towritelen = ft_strlen(data->dshd.towrite);
	data->linetemp = NULL;
	data->linetemp = ft_calloc(data->dshd.linelen + 1, sizeof(char));
}
