/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:22 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/20 15:11:21 by fbouchar         ###   ########.fr       */
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
		data->envp = env_cpy(envp, 0);
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
		ft_printf("emman\n");
		// while(ft_strncmp(envp[i], "_=", 2))
		// {
		// 	ft_printf("%s\n", envp[i++]);
		// }
		// mini_execute(data);
		ft_printf("%s\n", getenv("PATH"));

	}

	if(frank)
	{
		ft_printf("frank\n");
		if (argc != 1)
			exit(EXIT_FAILURE);  //TODO fonction de sorti à faire
		mini_start(data);
	}
}
