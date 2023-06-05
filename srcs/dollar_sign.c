/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:46:58 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/05 11:32:23 by fbouchar         ###   ########.fr       */
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
		// ft_printf("%s", data->dolsign.towrite);
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
	// ft_printf("%i\n", data->dolsign.len);
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
	// ft_printf("%i\n", ft_strlen(data->dolsign.tocheck));
	// ft_printf("->%s\n", data->dolsign.tocheck);
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
	data->linetemp = malloc(sizeof(char) * line + 1);
	if (data->line[i] != '\0')
	{
		while (data->line[i])
		{
			data->linetemp[i] = data->line[i];
			i++;
		}
		data->linetemp[i] = '\0';
		i = 0;
		free (data->line);//----------
	}
	data->line = malloc(sizeof(char) * (line + towrite - (tocheck + 1)) + 1);
	if (!data->line)
		mini_free(data);
	ft_printf("TEST1\n");
	if (data->linetemp[i] != '\0')
	{
		line = data->dolsign.start - 2;
		ft_printf("%i", line);
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
	ft_printf("%i", data->j);
	ft_printf("%i", i);
	// data->line[data->j] = '\0';
	free (data->linetemp);
}