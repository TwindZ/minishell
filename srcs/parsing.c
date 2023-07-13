/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:54:41 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/13 11:20:20 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	prep_line(t_data *data)
{
	int	len;

	data->i = 0;
	data->j = 0;
	len = ft_strlen(data->read);
	data->line = ft_safe_calloc(len + 5, sizeof(char), data);
	while (data->read[data->i] && data->read[data->i] != '\n')
	{
		in_quotes(data);
		dollar_sign(data);
		dollar_question(data);
		meta_chars(data, '|');
		meta_chars(data, '<');
		meta_chars(data, '>');
		transform_spaces(data);
		write_chars(data);
	}
}

int	ft_whitespace(t_data *data)
{
	char	*str;

	str = NULL;
	str = ft_strdup(data->read);
	//TODO si null?
	data->i = 0;
	while ((str[data->i] == ' '
			|| (str[data->i] >= 9 && str[data->i] <= 13)) && str[data->i])
		data->i++;
	if (str[data->i] == '\0')
	{
		freenull(str);
		return (0);
	}
	freenull(str);
	return (1);
}

void	transform_spaces(t_data *data)
{
	if (data->read[data->i] == ' ')
	{
		if (data->j > 0 && data->line[data->j - 1] != 29)
			data->line[data->j++] = 29;
		data->i++;
	}
}

void	write_chars(t_data *data)
{
	while (data->read[data->i] >= 33 && data->read[data->i] <= 126
		&& data->read[data->i] != '$' && data->read[data->i] != '|'
		&& data->read[data->i] != '<' && data->read[data->i] != '>')
	{
		if (data->read[data->i] == '"' || data->read[data->i] == 39)
			break ;
		data->line[data->j++] = data->read[data->i++];
	}
}
