/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:22 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/12 11:32:15 by fbouchar         ###   ########.fr       */
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
			exit (1);
		build_env(data, envp);
	}
	return (data);
}

int	parse(t_data *data)
{
	if (ft_strlen(data->read) == 0)
		return (1);
	add_history(data->read);
	if (ft_whitespace(data) == 0)
		return (1);
	if (fuckin_quotes(data) == -1)
		return (1);
	prep_line(data);
	if (ft_strlen(data->line) == 0)
		return (1);
	ft_printf("%s\n", data->line);
	make_list_ltkn(data);
	if(!data->ltkn || data->temp_in_mod == -1)
		return (1);
	return (0);
}

void	close_fd(t_data *data)
{
	if(data->fd.cmd_in > 2)
		close(data->fd.cmd_in);
	if(data->fd.cmd_next_in > 2)
		close(data->fd.cmd_next_in);
	if(data->fd.cmd_out > 2)
		close(data->fd.cmd_out);
}

void	mini_reset(t_data *data)
{
	if(data->ltkn)
		free_list_ltkn(data->ltkn);
	data->ltkn = NULL;
	if(data->line)
		free(data->line);
	if(data->read)
		free (data->read);
	ft_bzero(&data->exe_flag, sizeof(data->exe_flag));
	close_fd(data);
	ft_bzero(&data->fd, sizeof(data->fd));
	if(data->hd.data)
		free(data->hd.data);
	ft_bzero(&data->hd, sizeof(data->hd));
	data->temp_infile = NULL;
	data->temp_outfile =  NULL;
	data->temp_in_mod = 0;
	data->temp_out_mod = 0;
	data->read = NULL;
	data->line = NULL;
	data->hdprocess = 0;
	data->exeprocess = 0;
	free(data->pid.pid);
	ft_bzero(&data->pid, sizeof(data->pid));
}

// void	main_core(char **envp)
// {
	
// }

int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	if (argc > 1)
		return (0);
	t_data				*data;

	data = ft_init_data(envp);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	// signal(SIGQUIT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		while (1)
		{
			data->read = readline("Minishell>");
			// ft_printf("data_read %s", data->read);
			if(!data->read)
			{
				// rl_replace_line("Minishell>exit salut", 0);
				mini_exit(data, data->ltkn);
			}
				
			data->rdflag = 1;
			ft_printf("---------------------------------------\n");
			ft_printf("*****************DEBUG*****************\n");
			if (parse(data))
			{
				mini_reset(data);
				break ;
			}
			print_list(data);
			ft_printf("**-^-^-^-^-^-^-^-DEBUG-^-^-^-^-^-^-^-**\n");
			ft_printf("---------------------------------------\n");
			mini_execute(data);
			mini_reset(data);
		}
	}
	// main_core(envp);
}
//TODO reconvertir les caratere qui on ete changer durant le parsing
