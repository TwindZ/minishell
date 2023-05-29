/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:54:41 by fbouchar          #+#    #+#             */
/*   Updated: 2023/05/29 13:00:04 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_start(t_data *data)
{
	while (1)
	{
		if (data->rdflag == 1)
			free (data->read);
		data->read = readline("Minishell>");
		data->rdflag = 1;
		add_history(data->read);
		dquotes(data);
		squotes(data);
	}
}

void	dquotes(t_data *data)
{
	int	i;

	i = 0;
	while (data->read[i])
	{
		if (data->read[i++] == '"')
			data->dquote += 1;
	}
	if (data->dquote % 2 != 0)
	{	
		ft_printf("Double quote missing\n");
		mini_exit(data);
	}
}

void	squotes(t_data *data)
{
	int	i;

	i = 0;
	while (data->read[i])
	{
		if (data->read[i++] == 39)
			data->squote += 1;
	}
	if (data->squote % 2 != 0)
	{	
		if (data->dquote % 2 != 0 || data->dquote == 0)
		{
			ft_printf("Single quote missing\n");
			mini_exit(data);
		}
	}
}