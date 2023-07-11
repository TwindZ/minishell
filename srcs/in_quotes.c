/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:23:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/11 13:27:40 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	in_quotes(t_data *data)
{
	if (data->read[data->i] == '"')
	{
		data->i++;
		while (data->read[data->i] != '"')
			in_double_quotes(data);
		data->i++;
	}
	if (data->read[data->i] == 39)
	{
		data->i++;
		while (data->read[data->i] != 39)
		{
			if (data->read[data->i] != '|' && data->read[data->i] != '>'
				&& data->read[data->i] != '<')
				data->line[data->j++] = data->read[data->i++];
			replace_meta(data);
		}
		data->i++;
	}
}

void	in_double_quotes(t_data *data)
{
	if (data->read[data->i] != '$' && data->read[data->i] != '|'
		&& data->read[data->i] != '>' && data->read[data->i] != '<')
		data->line[data->j++] = data->read[data->i++];
	dollar_sign(data);
	dollar_question(data);
	replace_meta(data);
}
