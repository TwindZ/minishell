/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_question.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:51:03 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/13 10:12:49 by emlamoth         ###   ########.fr       */
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
		// TODO itoa NULL return
		while (out[i])
			data->line[data->j++] = out[i++];
		freenull(out);
	}
}
