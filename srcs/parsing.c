/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:54:41 by fbouchar          #+#    #+#             */
/*   Updated: 2023/05/30 15:33:51 by fbouchar         ###   ########.fr       */
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
		if (!data->read)
			mini_exit(data);
		data->rdflag = 1;
		add_history(data->read);
		dquotes(data);
		squotes(data);
		prep_line(data);
		make_list(data);
		// print_list(data);
		check_path(data);
		ft_printf("%s\n", data->lcmd->cmdpath);
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
	int	len;

	data->i = 0;
	data->j = 0;
	len = ft_strlen(data->read);
	data->line = malloc(sizeof(char) * len + 1);
	if (!data->line)
		mini_exit(data);
	while (data->read[data->i])
	{
		if (data->read[data->i] == ' ')
		{
			if (data->line[data->j - 1] != '\t')
				data->line[data->j++] = '\t';
			data->i++;
		}
		while (data->read[data->i] >= 33 && data->read[data->i] <= 126)
		{
			if (data->read[data->i] == '"')
				break;
			data->line[data->j++] = data->read[data->i++];
		}
		in_quotes(data);
	}
	data->line[data->j] = '\0';
}

void	in_quotes(t_data *data)
{
	if (data->read[data->i] == '"')
	{
		if (data->line[data->j - 1] != '\t')
			data->line[data->j++] = '\t';
		data->i++;
		while (data->read[data->i] != '"')
			data->line[data->j++] = data->read[data->i++];
		if (data->line[data->j - 1] != '\t')
			data->line[data->j++] = '\t';
		data->i++;
	}
}