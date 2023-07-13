/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:22 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/13 10:15:50 by fbouchar         ###   ########.fr       */
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
		//TODO erreur ?
		build_env(data, envp);
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
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
	if(data->line)
		freenull(data->line);
	if(data->read)
		freenull(data->read);
	ft_bzero(&data->exe_flag, sizeof(data->exe_flag));
	close_fd(data);
	ft_bzero(&data->fd, sizeof(data->fd));
	if(data->hd.data)
		freenull(data->hd.data);
	ft_bzero(&data->hd, sizeof(data->hd));
	if(data->temp_infile)
		freenull(data->temp_infile);
	if(data->temp_outfile)
		freenull(data->temp_outfile);
	data->temp_in_mod = 0;
	data->temp_out_mod = 0;
	data->hdprocess = 0;
	data->exeprocess = 0;
	freenull(data->pid.pid);
	ft_bzero(&data->pid, sizeof(data->pid));
}

int	main(int argc, char **argv, char **envp)
{
	(void)	argv;
	t_data	*data;
	
	if (argc > 1)
		return (0);
	data = ft_init_data(envp);
	while (1)
	{
		while (1)
		{
			data->read = readline("Minishell>");
			// ft_printf("data_read %s", data->read);
			if(!data->read)
				mini_exit(data, data->ltkn);
			data->rdflag = 1;
			// ft_printf("---------------------------------------\n");
			// ft_printf("*****************DEBUG*****************\n");
			if (parse(data))
			{
				mini_reset(data);
				break ;
			}
			// print_list(data);
			// ft_printf("**-^-^-^-^-^-^-^-DEBUG-^-^-^-^-^-^-^-**\n");
			// ft_printf("---------------------------------------\n");
			mini_execute(data);
			ft_waiting(data);
			mini_reset(data);
		}
	}
}
//TODO reconvertir les caratere qui on ete changer durant le parsing
