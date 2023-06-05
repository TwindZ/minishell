/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:54:41 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/05 14:46:02 by fbouchar         ###   ########.fr       */
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
	data->line = ft_calloc(len + 1, sizeof(char));
	if (!data->line)
		mini_free(data);
	while (data->read[data->i])
	{
		ft_printf("TEST\n");
		in_quotes(data);
		dollar_sign(data);
		if (data->read[data->i] == ' ')
		{
			if (data->line[data->j - 1] != '\t')
				data->line[data->j++] = '\t';
			data->i++;
		}
		while (data->read[data->i] >= 33 && data->read[data->i] <= 126
			&& data->read[data->i] != '$')
		{
			if (data->read[data->i] == '"' || data->read[data->i] == 39)
				break;
			data->line[data->j++] = data->read[data->i++];
		}
	}
}

void	in_quotes(t_data *data)
{
	if (data->read[data->i] == '"')
	{
		data->i++;
		// dollar_sign(data);
		while (data->read[data->i] != '"')
		{
			if (data->read[data->i] != '$')
				data->line[data->j++] = data->read[data->i++];
			dollar_sign(data);
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
