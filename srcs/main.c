/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:22 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/06 10:49:59 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#define emman 0
#define frank 1

t_data *ft_init_data(char **envp)
{
	static t_data *data;
	
	if(!data)
	{
		data = ft_calloc(1, sizeof(t_data));
		if(!data)
			return (NULL);
		data->envp = envp;
		// data->lcmd = NULL;
		// data->ltkn = NULL;
		// data->path = NULL;
		// data->read = NULL;
		// data->line = NULL;
		// data->rdflag = 0;
		// data->i = 0;
		// data->j = 0;
		// data->lcmd = NULL;
		// data->ltkn = NULL;
		// data->path = NULL;
		// data->fd.cmd_next_in = 0;
		// data->fd.cmd_in = -1;
		// data->fd.cmd_out = -1;
		// data->exe_flag.file_out_a = 0;
		// data->exe_flag.file_out_w = 0;
		// data->exe_flag.file_in = 0;
		// data->exe_flag.front_pipe = 0;
		// data->exe_flag.back_pipe = 0;
		// data->read = NULL;
		// data->line = NULL;
		// data->rdflag = 0;
		// data->i = 0;
		// data->j = 0;
	}
	return (data);
}

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;

	t_data *data;

	data = ft_init_data(envp);
	
	if(emman)
	{
		int i;
		i = 0;
		ft_printf("emman\n");
		// while(ft_strncmp(envp[i], "_=", 2))
		// {
		// 	ft_printf("%s\n", envp[i++]);
		// }
		mini_execute(data);
	}

	if(frank)
	{
		ft_printf("frank\n");
		if (argc != 1)
			exit(EXIT_FAILURE);  //TODO fonction de sorti à faire
		mini_start(data);
	}
}
