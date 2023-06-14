/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:29:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/14 17:00:33 by emlamoth         ###   ########.fr       */
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
			}
			data->read = readline("Minishell>");
			data->rdflag = 1;
			if (ft_strncmp(data->read, "exit", 4) == 0)
			{
				mini_free(data);
				exit(EXIT_SUCCESS);
			}
			ft_printf("ministep\n");
			if (ft_strlen(data->read) == 0)
				break ;
			ft_printf("ministep2\n");
			add_history(data->read);
			if (whitespace(data) == 0)
				break ;
			if (fuckin_quotes(data) == -1)
				break ;
			prep_line(data);
			if (ft_strlen(data->line) == 0)
				break ;
			ft_printf("%s\n", data->line);
			make_list_ltkn(data);
			mini_execute(data);
			print_list(data);
			free_list_ltkn(data->ltkn);
			mini_free(data);
			ft_bzero(data, sizeof(t_data));
		}
	}
}
