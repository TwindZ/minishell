/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:22 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/18 07:36:18 by emman            ###   ########.fr       */
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
	if (!data->ltkn || data->temp_in_mod == -1)
		return (1);
	return (0);
}

void	close_fd(t_data *data)
{
	if (data->fd.cmd_in > 2)
		close(data->fd.cmd_in);
	if (data->fd.cmd_next_in > 2)
		close(data->fd.cmd_next_in);
	if (data->fd.cmd_out > 2)
		close(data->fd.cmd_out);
}

void	mini_reset(t_data *data)
{
	free_reset(data);
	ft_bzero(&data->exe_flag, sizeof(data->exe_flag));
	close_fd(data);
	ft_bzero(&data->fd, sizeof(data->fd));
	if (data->hd.data)
		free(data->hd.data);
	ft_bzero(&data->hd, sizeof(data->hd));
	if (data->temp_infile)
		free(data->temp_infile);
	data->temp_infile = NULL;
	if (data->temp_outfile)
		free(data->temp_outfile);
	data->temp_outfile = NULL;
	// if (data->lastwd)
	// 	free(data->lastwd);
	data->temp_in_mod = 0;
	data->temp_out_mod = 0;
	data->hdprocess = 0;
	data->exeprocess = 0;
	data->syntax = 0;
	// data->execve_free = 0;
	free(data->pid.pid);
	ft_bzero(&data->pid, sizeof(data->pid));
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argv;
	if (argc > 1)
		return (0);
	data = ft_init_data(envp);
	while (1)
	{
		while (1)
		{
			// int i;
			// i = 0
			// char **dest;
			// dest = ft_tabcpy(data->envp);
			// while(dest[i])
			// {
			// 	i++;
			// }
			data->read = readline("Minishell>");
			if (!data->read)
				mini_exit(data, data->ltkn);
			data->rdflag = 1;
			if (parse(data))
			{
				mini_reset(data);
				break ;
			}
			mini_execute(data);
			ft_waiting(data);
			mini_reset(data);
		}
	}
}
