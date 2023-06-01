/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:46:58 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/01 14:54:49 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	dollar_sign(t_data *data)
{
	init_dollar(data);
	if (data->read[data->i] == '$')
	{
		make_tocheck(data);
		data->dolsign.towrite = getenv(data->dolsign.tocheck);
		ft_printf("%s", data->dolsign.towrite);
		free(data->dolsign.tocheck);
		if (data->dolsign.towrite == NULL)
			data->i = data->dolsign.start - 1;
	}
}

void	init_dollar(t_data *data)
{
	data->dolsign.start = 0;
	data->dolsign.end = 0;
	data->dolsign.len = 0;
	data->dolsign.idx = 0;
	data->dolsign.tocheck = NULL;
	data->dolsign.towrite = NULL;
}

void	make_tocheck(t_data *data)
{
	data->i++;
	data->dolsign.start = data->i;
	while ((data->read[data->i] >= 65 && data->read[data->i] <= 90)
		|| (data->read[data->i] >= 97 && data->read[data->i] <= 121)
		|| (data->read[data->i] >= 48 && data->read[data->i] <= 57)
		|| data->read[data->i] == '_' )
		data->i++;
	data->dolsign.end = data->i;
	data->dolsign.len = data->dolsign.end - data->dolsign.start;
	ft_printf("%i\n", data->dolsign.len);
	data->dolsign.tocheck = malloc(sizeof(char) * data->dolsign.len + 1);
	if (!data->dolsign.tocheck)
		mini_free(data);
	while (data->dolsign.start < data->dolsign.end)
	{
		data->dolsign.tocheck[data->dolsign.idx] = data->read[data->dolsign.start];
		data->dolsign.start++;
		data->dolsign.idx++;
	}
	data->dolsign.tocheck[data->dolsign.idx] = '\0';
	ft_printf("%i\n", ft_strlen(data->dolsign.tocheck));
	ft_printf("->%s\n", data->dolsign.tocheck);
}