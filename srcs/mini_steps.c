/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:29:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/20 14:46:26 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_start(t_data *data)
{
	char **temp_env;

	temp_env = NULL;
	while (1)
	{
		while (1)
		{
			data->read = readline("Minishell>");
			data->rdflag = 1;
			if (ft_strncmp(data->read, "exit", 4) == 0)
				mini_exit(data);
			if (ft_strlen(data->read) == 0)
				break ;
			add_history(data->read);
			if (whitespace(data) == 0)
				break ;
			if (fuckin_quotes(data) == -1)
				break ;
			prep_line(data); ///1
			if (ft_strlen(data->line) == 0)
				break ;
			ft_printf("%s\n", data->line);
			make_list_ltkn(data);
			print_list(data);
			mini_execute(data);
			free_list_ltkn(data->ltkn);
			free(data->line);
			free (data->read);
			temp_env = data->envp;
			ft_bzero(data, sizeof(t_data));
			data->envp = temp_env;
			
		}
	}
}
