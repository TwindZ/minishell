/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:39:37 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/12 14:06:59 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	fuckin_quotes(t_data *data)
{
	init_quotes(data);
	while (data->read[data->quotes.idx])
	{
		if (data->read[data->quotes.idx] == '"'
			|| data->read[data->quotes.idx] == 39)
		{
			double_quotes(data);
			single_quotes(data);
			quotes_priority(data);
		}
		data->quotes.idx++;
	}
	if (data->quotes.dbl % 2 != 0)
	{
		ft_putstr_fd("double quote missing\n", 2);
		data->prevout = 1;
		return (-1);
	}
	if (data->quotes.sgl % 2 != 0)
	{
		ft_printf("single quote missing\n");
		data->prevout = 1;
		return (-1);
	}
	return (0);
}

void	init_quotes(t_data *data)
{
	data->quotes.idx = 0;
	data->quotes.dbl = 0;
	data->quotes.sgl = 0;
	data->quotes.dblflag = 0;
	data->quotes.sglflag = 0;
	data->quotes.dblflag = 0;
	data->quotes.spotsgl = 0;
	data->quotes.spotdbl = 0;
}

void	double_quotes(t_data *data)
{
	if (data->read[data->quotes.idx] == '"')
	{
		if (data->quotes.dblflag == 1 && data->quotes.sglflag == 0)
			data->quotes.dblflag = 0;
		else
			data->quotes.dblflag = 1;
		data->quotes.spotdbl = data->quotes.idx;
		data->quotes.dbl += 1;
	}
}

void	single_quotes(t_data *data)
{
	if (data->read[data->quotes.idx] == 39)
	{
		if (data->quotes.sglflag == 1 && data->quotes.dblflag == 0)
			data->quotes.sglflag = 0;
		else
			data->quotes.sglflag = 1;
		data->quotes.spotsgl = data->quotes.idx;
		data->quotes.sgl += 1;
	}
}

void	quotes_priority(t_data *data)
{
	if (data->quotes.sglflag == 1 && data->quotes.dblflag == 1)
	{
		if (data->quotes.spotdbl < data->quotes.spotsgl)
		{
			data->quotes.sglflag = 0;
			data->quotes.spotdbl = 0;
			data->quotes.sgl -= 1;
		}
		else
		{
			data->quotes.dblflag = 0;
			data->quotes.spotsgl = 0;
			data->quotes.dbl -= 1;
		}
	}
}
