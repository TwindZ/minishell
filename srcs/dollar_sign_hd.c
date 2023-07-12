/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_hd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:43:01 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/11 14:46:02 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TODO gérer le $? et les sorties d'erreurs
void	dollar_sign_hd(t_data *data)
{
	char *test;
	
	test = NULL;
	init_dollar_hd(data);
	if (data->readhd[data->hd.i] == '$')
	{
		// if (data->read[data->i + 1] == '?')
		// 	return ;
		if (data->readhd[data->hd.i + 1] == ' ' || data->readhd[data->hd.i + 1]
			== '\0' || data->readhd[data->i + 1] == '"')
		{
			// data->hd.i++;
			return ;
		}
		data->dshd.flag = 1;
		make_tocheck_hd(data);
		data->dshd.towrite = getenvp(data, data->dshd.tocheck, 1);
		ft_printf("%i\n", data->dshd.start2);
		if (data->dshd.towrite != NULL)
			adjust_line_hd(data);
		else
			test = ft_substr(data->readhd, data->dshd.start2, ft_strlen(data->dshd.tocheck));
		ft_printf("%s\n", test);
		freenull(data->dshd.tocheck);
		freenull(data->dshd.towrite);
	}
	else if (data->dshd.flag == 1 && data->readhd[data->hd.i])
	{
		data->readhd[data->dshd.start2++] = data->linetemp[data->hd.i];
	}
}
//TODO faire une modif comme la fonction dollar_sign
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
	while ((data->readhd[data->hd.i] >= 65 && data->readhd[data->hd.i] <= 90)
		|| (data->readhd[data->hd.i] >= 97 && data->readhd[data->hd.i] <= 121)
		|| (data->readhd[data->hd.i] >= 48 && data->readhd[data->hd.i] <= 57)
		|| data->readhd[data->hd.i] == '_' )
		data->hd.i++;
	data->dshd.end = data->hd.i;
	data->dshd.len = data->dshd.end - data->dshd.start;
	data->dshd.tocheck = ft_safe_calloc(data->dshd.len + 2, sizeof(char), data);
	while (data->dshd.start < data->dshd.end)
	{
		data->dshd.tocheck[data->dshd.idx]
			= data->readhd[data->dshd.start++];
		if (data->dshd.tocheck[0] >= 48 && data->dshd.tocheck[0] <= 57)
		{
			data->hd.i = data->dshd.start;
			break ;
		}
		data->dshd.idx++;
	}
	data->dshd.tocheck = ft_strjoin(data->dshd.tocheck, "=", 1);
}

void	adjust_line_hd(t_data *data)
{
	init_adjust_hd(data);
	while (data->dshd.i < data->dshd.linelen || data->readhd[data->dshd.i])
	{
		data->linetemp[data->dshd.i] = data->readhd[data->dshd.i];
		data->dshd.i++;
	}
	data->dshd.i = 0;
	freenull(data->readhd);
	ft_printf("%i\n", data->dshd.towritelen);
	data->readhd = ft_safe_calloc((data->dshd.linelen
				+ data->dshd.towritelen), sizeof(char), data);
	while (data->linetemp[data->dshd.i])
	{
		data->readhd[data->dshd.i] = data->linetemp[data->dshd.i];
		data->dshd.i++;
	}
	data->dshd.i = 0;
	while (data->dshd.towritelen-- != 0)
		data->readhd[data->dshd.start2++] = data->dshd.towrite[data->dshd.i++];
	data->readhd[data->dshd.start2++] = ' ';
	// if (data->linetemp != NULL)
	// 	freenull(data->linetemp);
}

void	init_adjust_hd(t_data *data)
{
	data->dshd.i = 0;
	data->dshd.linelen = ft_strlen(data->readhd);
	data->dshd.towritelen = ft_strlen(data->dshd.towrite);
	data->linetemp = NULL;
	data->linetemp = ft_safe_calloc(data->dshd.linelen + 1, sizeof(char), data);
}
