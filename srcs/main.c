/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:22 by emlamoth          #+#    #+#             */
/*   Updated: 2023/05/30 10:20:16 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define emman 1
#define frank 0

t_data *ft_init_data(char **envp)
{
	static t_data *data;
	
	if(!data)
	{
		data = malloc(sizeof(t_data));
		if(!data)
			return (NULL);
		data->envp = envp;
		data->lcmd = NULL;
		data->ltkn = NULL;
		data->path = NULL;
		data->oldfdr = 0;
		data->front_pipe = 0;
		data->back_pipe = 0;
		data->read = NULL;
		data->line = NULL;
		data->rdflag = 0;
		data->dquote = 0;
		data->squote = 0;
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
			mini_exit(data);
		mini_start(data);
	}
	
}