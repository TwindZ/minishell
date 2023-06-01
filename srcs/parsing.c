/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:54:41 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/01 15:12:39 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	whitespace(t_data *data)
{
	char *str;

	str = data->read;
	data->i = 0;
	while ((str[data->i] == ' '
		|| (str[data->i] >= 9 && str[data->i] <= 13)) && str[data->i])
		data->i++;
	if (str[data->i] == '\0')
		return (0);
	return (1);
}

void	prep_line(t_data *data)
{
	int	len;

	data->i = 0;
	data->j = 0;
	len = ft_strlen(data->read);
	data->line = malloc(sizeof(char) * len + 1);
	if (!data->line)
		mini_free(data);
	while (data->read[data->i])
	{
		dollar_sign(data);
		if (data->read[data->i] == ' ')
		{
			if (data->line[data->j - 1] != '\t')
				data->line[data->j++] = '\t';
			data->i++;
		}
		while (data->read[data->i] >= 33 && data->read[data->i] <= 126)
		{
			dollar_sign(data);
			if (data->read[data->i] == '"' || data->read[data->i] == 39)
				break;
			data->line[data->j++] = data->read[data->i++];
		}
		in_quotes(data);
	}
	data->line[data->j] = '\0';
}

void	in_quotes(t_data *data)
{
	if (data->read[data->i] == '"')
	{
		data->i++;
		dollar_sign(data);
		while (data->read[data->i] != '"')
		{
			data->line[data->j++] = data->read[data->i++];
		}
		data->i++;
	}
	if (data->read[data->i] == 39)
	{
		data->i++;
		while (data->read[data->i] != 39)
			data->line[data->j++] = data->read[data->i++];
		data->i++;
	}
}
