/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dshd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:21:44 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/31 20:36:31 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
This function duplicates the line, substituting environment variables with
corresponding data and preserving the rest of the line. */
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

/*This function retrieves data from the environment variable.*/
void	get_var_data(t_data *data)
{
	data->dshd.j = 0;
	data->dshd.var = ft_safe_calloc(data->dshd.varlen + 2,
			sizeof(char), data);
	ft_strlcpy(data->dshd.var, data->dshd.templine
		+ data->dshd.save_j + 1, data->dshd.varlen + 1);
	data->dshd.var = ft_strjoin(data->dshd.var, "=", 1);
	if (!data->dshd.var)
		exit_free(data, 1);
	data->dshd.vardata = getenvp(data, data->dshd.var, 1);
	free(data->readhd);
	data->readhd = ft_safe_calloc(ft_strlen(data->dshd.vardata)
			+ ft_strlen(data->dshd.templine) + 2, sizeof(char), data);
}

/*This function temporarily replaces a standalone dollar sign with the ASCII 29
character; otherwise, it substitutes it with the corresponding environment
variable.*/
void	dol_resolve(t_data *data)
{
	if (data->dshd.varlen == 0)
	{
		data->dshd.templine[data->dshd.j - 1] = 29;
		data->readhd = ft_mini_strdup(data->dshd.templine, data);
		free(data->dshd.templine);
		data->dshd.templine = NULL;
	}
	else
	{
		get_var_data(data);
		read_maker(data);
	}
}

/*This function converts environment variables present in the heredoc input.*/
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
			data->dshd.j++;
		data->dshd.varlen = data->dshd.j - (data->dshd.save_j + 1);
		dol_resolve(data);
	}
	data->dshd.i = 0;
	while (data->readhd[data->dshd.i])
	{
		if (data->readhd[data->dshd.i] == 29)
			data->readhd[data->dshd.i] = '$';
		data->dshd.i++;
	}
}
