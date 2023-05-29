/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:54:41 by fbouchar          #+#    #+#             */
/*   Updated: 2023/05/29 15:35:42 by fbouchar         ###   ########.fr       */
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
		prep_line(data);
		ft_printf("%s\n", data->line);
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

void	prep_line(t_data *data)
{
	int i;
	int j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	len = ft_strlen(data->read);
	data->line = malloc(sizeof(char) * len + 1);
	if (!data->line)
		mini_exit(data);
	while (data->read[i])
	{
		while (data->read[i] == ' ' || data->read[i] == '\t')
		{
			if (data->line[j - 1] != '\t')
				data->line[j++] = '\t';
			i++;
		}
		if (data->read[i] == '"')
		{
			data->line[j++] = '\t';
			i++;
			while (data->read[i] != '"')
			{
				data->line[j++] = data->read[i++];
				if (data->read[i] == '"')
					data->line[j] = '\t';
			}
			// data->line[j] = '\t';
		}
		while (data->read[i] >= 33 && data->read[i] <= 126)
		{
			// if (data->read[i] == '"')
			// 	break;
			data->line[j] = data->read[i];
			i++;
			j++;
		}
	}
	data->line[j] = '\0';
}