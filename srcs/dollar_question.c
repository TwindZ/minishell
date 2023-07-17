/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_question.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:51:03 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/17 10:35:46 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dollar_question(t_data *data)
{
	char	*out;
	int		i;

	i = 0;
	out = NULL;
	if (data->read[data->i] == '$' && data->read[data->i + 1] == '?')
	{
		data->i += 2;
		out = ft_itoa(data->prevout);
		if (!out)
			exit_free(data, 1);
		while (out[i])
			data->line[data->j++] = out[i++];
		free(out);
	}
}
