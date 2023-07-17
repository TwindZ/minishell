/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:47:35 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/17 09:49:59 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replace_meta(t_data *data)
{
	if (data->read[data->i] == '|' || data->read[data->i] == '<'
		|| data->read[data->i] == '>')
	{
		if (data->read[data->i] == '|')
			data->line[data->j++] = 28;
		if (data->read[data->i] == '<')
			data->line[data->j++] = 30;
		if (data->read[data->i] == '>')
			data->line[data->j++] = 31;
		data->i++;
	}
}

void	meta_replace(t_ltkn *temp)
{
	int	i;
	int	j;

	j = 1;
	while (temp->arg[j])
	{
		i = 0;
		while (temp->arg[j][i])
		{
			if (temp->arg[j][i] == 28)
				temp->arg[j][i++] = '|';
			else if (temp->arg[j][i] == 30)
				temp->arg[j][i++] = '<';
			else if (temp->arg[j][i] == 31)
				temp->arg[j][i++] = '>';
			else
				i++;
		}
		j++;
	}
}
