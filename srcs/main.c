/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:22 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/28 14:26:36 by emlamoth         ###   ########.fr       */
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
		build_env(data, envp);
	}
	return (data);
}

void	mini_exit(t_data *data)
{
	ft_printf("exit\n");
	free_list_ltkn(data->ltkn);
	free (data->read);
	ft_freeall(data->envp);
	free (data);
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

void	mini_reset(t_data *data)
{
	free_list_ltkn(data->ltkn);
	data->ltkn = NULL;
	free(data->line);
	free (data->read);
	ft_bzero(&data->exe_flag, sizeof(data->exe_flag));
	ft_bzero(&data->fd, sizeof(data->fd));
	ft_bzero(&data->hd, sizeof(data->hd));
	data->temp_infile = NULL;
	data->temp_outfile =  NULL;
	data->temp_in_mod = 0;
	data->temp_out_mod = 0;
}

void block_signal(int sig)
{
	sigset_t	sigset;
	
	sigemptyset(&sigset);
	sigaddset(&sigset, sig);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
}

void	main_core(char **envp)
{
	t_data				*data;
	struct sigaction	sa;
	
	data = ft_init_data(envp);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = &sig_handler;
	block_signal(SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
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
			mini_reset(data);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	if (argc > 1)
		return (0);
	main_core(envp);
}
