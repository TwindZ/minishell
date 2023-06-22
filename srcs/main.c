/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:22 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/22 15:04:50 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	*ft_init_data(char **envp)
{
	static t_data	*data;

	if (!data)
	{
		data = ft_calloc(1, sizeof(t_data));
		if (!data)
			return (NULL);
		data->envp = env_cpy(envp, 0);
	}
	return (data);
}

void	mini_exit(t_data *data)
{
	ft_printf("exit\n");
	free_list_ltkn(data->ltkn);
	free(data->read);
	ft_freeall(data->envp);
	free(data);
	exit(EXIT_SUCCESS);
}

int	parse(t_data *data)
{
	if (ft_strncmp(data->read, "exit", 4) == 0)
		mini_exit(data);
	if (ft_strlen(data->read) == 0)
		return (1);
	add_history(data->read);
	if (whitespace(data) == 0)
		return (1);
	if (fuckin_quotes(data) == -1)
		return (1);
	prep_line(data);
	if (ft_strlen(data->line) == 0)
		return (1);
	ft_printf("%s\n", data->line);
	make_list_ltkn(data);
	return (0);
}
//TODO a enlever

void	reset(t_data *data)
{
	char	**temp_env;

	temp_env = env_cpy(data->envp, 0);
	free_list_ltkn(data->ltkn);
	free(data->line);
	free (data->read);
	ft_freeall(data->envp);
	ft_bzero(data, sizeof(t_data));
	data->envp = temp_env;
}

int	main(int argc, char **argv, char **envp)
{
	t_data				*data;
	// struct sigaction	sa;

	(void) argv;
	if (argc > 1)
		return (0);
	// sa.sa_sigaction = &ft_sa_sigaction;
	// sa.sa_flags = SA_SIGINFO;
	// sigaction(SIGUSR1, &sa, NULL);
	// sigaction(SIGUSR2, &sa, NULL);
	data = ft_init_data(envp);
	
	while (1)
	{
		while (1)
		{
			data->read = readline("Minishell>");
			data->rdflag = 1;
			ft_printf("\n\n---------------------------------------\n");
			ft_printf("*****************DEBUG*****************\n");
			if (parse(data))
				break ;
			print_list(data);
			ft_printf("**-^-^-^-^-^-^-^-DEBUG-^-^-^-^-^-^-^-**\n");
			ft_printf("---------------------------------------\n");
			mini_execute(data);
			reset(data);
		}
	}
}
