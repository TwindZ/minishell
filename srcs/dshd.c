/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dshd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:21:44 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/13 11:52:35 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

void	read_maker(t_data *data)
{
	while (data->dshd.templine[data->dshd.j])
	{
		if (data->dshd.templine[data->dshd.j] == '$')
			break ;
		data->readhd[data->dshd.i++] = data->dshd.templine[data->dshd.j++];
	}
	if (data->dshd.vardata)
	{
		while (data->dshd.vardata[data->dshd.k])
			data->readhd[data->dshd.i++] = data->dshd.vardata[data->dshd.k++];
		data->dshd.k = 0;
	}
	data->dshd.j++;
	while (var_char(data->dshd.templine[data->dshd.j])
		&& data->dshd.templine[data->dshd.j])
		data->dshd.j++;
	while (data->dshd.templine[data->dshd.j])
		data->readhd[data->dshd.i++] = data->dshd.templine[data->dshd.j++];
	freenull(data->dshd.templine);
	if (data->dshd.vardata)
		freenull(data->dshd.vardata);
	freenull(data->dshd.var);
}

void	dshd(t_data *data)
{
	while (dollar(data->readhd))
	{
		ft_bzero(&data->dshd, sizeof(data->dshd));
		data->dshd.templine = ft_mini_strdup(data->readhd, data);
		while (data->dshd.templine[data->dshd.j] != '$')
			data->dshd.j++;
		data->dshd.save_j = data->dshd.j;
		data->dshd.j++;
		while (var_char(data->dshd.templine[data->dshd.j])
			&& data->dshd.templine[data->dshd.j])
		{
			data->dshd.varlen++;
			data->dshd.j++;
		}
		data->dshd.j = 0;
		data->dshd.var = ft_safe_calloc(data->dshd.varlen + 2, sizeof(char), data);
		ft_strlcpy(data->dshd.var, data->dshd.templine
			+ data->dshd.save_j + 1, data->dshd.varlen + 1);
		data->dshd.var = ft_strjoin(data->dshd.var, "=", 1);
		//TODO si NULL
		data->dshd.vardata = getenvp(data, data->dshd.var, 1);
		// TODO si NULL
		free(data->readhd);
		data->readhd = ft_safe_calloc(ft_strlen(data->dshd.vardata)
				+ ft_strlen(data->dshd.templine) + 2, sizeof(char), data); 
		read_maker(data);
	}
}
