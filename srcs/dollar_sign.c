/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:46:58 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/05 14:45:57 by fbouchar         ###   ########.fr       */
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
		if (data->dolsign.towrite != NULL)
			adjust_line(data);
		free(data->dolsign.tocheck);
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
}

void	adjust_line(t_data *data)
{
	int i;
	int	line;
	int	tocheck;
	int towrite;

	i = 0;
	line = ft_strlen(data->line);
	tocheck = ft_strlen(data->dolsign.tocheck);
	towrite = ft_strlen(data->dolsign.towrite);
	data->linetemp = NULL;//------------
	data->linetemp = ft_calloc(line + 1, sizeof(char));
	if (data->line[i] != '\0')
	{
		while (data->line[i])
		{
			ft_printf("--%c--\n", data->line[i]);
			data->linetemp[i] = data->line[i];
			i++;
		}
		i = 0;
		free (data->line);//----------
	}
	data->line = ft_calloc((line + towrite), sizeof(char));
	ft_printf("%i\n", line);
	ft_printf("%i\n", towrite);
	ft_printf("%i\n", (line + towrite + 1));
	if (!data->line)
		mini_free(data);
	if (data->linetemp[i] != '\0')
	{
		line = data->j + towrite;
		while (line != 0)//---------
		{
			data->line[i] = data->linetemp[i];
			i++;
			line--;
		}
		i = 0;
	}
	while (towrite != 0)
	{
		data->line[data->j] = data->dolsign.towrite[i];
		data->j++;
		i++;
		towrite--;
	}
	free (data->linetemp);
}