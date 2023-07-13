/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dshd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:21:44 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/13 18:34:29 by emlamoth         ###   ########.fr       */
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
	free(data->dshd.templine);
	if (data->dshd.vardata)
		free(data->dshd.vardata);
	free(data->dshd.var);
		
}
void	get_var_data(t_data *data)
{
	data->dshd.j = 0;
		data->dshd.var = ft_safe_calloc(data->dshd.varlen + 2, sizeof(char), data);
	ft_strlcpy(data->dshd.var, data->dshd.templine
		+ data->dshd.save_j + 1, data->dshd.varlen + 1);
	data->dshd.var = ft_strjoin(data->dshd.var, "=", 1);
	if(!data->dshd.var)
		exit_free(data, 1);
	data->dshd.vardata = getenvp(data, data->dshd.var, 1);
	if(!data->dshd.vardata)
		exit_free(data, 1);
	free(data->readhd);
	data->readhd = ft_safe_calloc(ft_strlen(data->dshd.vardata)
			+ ft_strlen(data->dshd.templine) + 2, sizeof(char), data);
}
void	dshd(t_data *data)
{
	dshd_init(data);
	while (dollar(data->readhd))
	{
		ft_bzero(&data->dshd, sizeof(data->dshd));
		data->dshd.templine = ft_mini_strdup(data->readhd, data);
		while (data->dshd.templine[data->dshd.j] != '$')
			data->dshd.j++;
		data->dshd.save_j = data->dshd.j;
		data->dshd.j++;
		while (data->dshd.templine[data->dshd.j] 
			&& var_char(data->dshd.templine[data->dshd.j]))
		{
			data->dshd.j++;
		}
		data->dshd.varlen = data->dshd.j - (data->dshd.save_j + 1);
		if(data->dshd.varlen == 0)
		{
			data->dshd.templine[data->dshd.j - 1] = 29;
			data->readhd = ft_mini_strdup(data->dshd.templine ,data);
		}	
		else
		{	
			get_var_data(data);
			read_maker(data);
		}
	}
		data->dshd.i = 0;
		while(data->readhd[data->dshd.i])
		{	
			if(data->readhd[data->dshd.i] == 29)
				data->readhd[data->dshd.i] = '$';
			data->dshd.i++;
		}
}
