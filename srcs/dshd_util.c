/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dshd_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:57:55 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/17 10:59:55 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dshd_init(t_data *data)
{
	data->dshd.templine = NULL;
	data->dshd.vardata = NULL;
	data->dshd.var = NULL;
	data->dshd.varlen = 0;
	data->dshd.j = 0;
	data->dshd.i = 0;
	data->dshd.k = 0;
	data->dshd.save_j = 0;
}

int	dollar(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}
