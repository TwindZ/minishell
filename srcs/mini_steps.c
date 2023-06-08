/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:29:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/06 16:07:08 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_start(t_data *data)
{
	while (1)
	{
		while (1)
		{
			if (data->rdflag == 1)
			{	
				free (data->read);
				// free (data->line);
			}
			data->read = readline("Minishell>");
			// if () ft_strncmp()
			data->rdflag = 1;
			if (ft_strlen(data->read) == 0)
				break;
			add_history(data->read);
			if (whitespace(data) == 0)
				break;
			if (fuckin_quotes(data) == -1)
				break;
			prep_line(data);
			if (ft_strlen(data->line) == 0)
				break;
			arg_list(data);
			// ft_printf("%s\n", data->line);
			// make_list(data);
			// check_path(data);
			// print_list(data);
			// mini_free(data);
			free (data->line);
		}
	}
}