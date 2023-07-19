/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:51:03 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/19 12:49:51 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	hd_out(t_data *data)
{
	data->fd.cmd_in = data->fd.cmd_next_in;
	ft_putstr_fd(data->hd.data, data->fd.cmd_out);
	if (data->fd.cmd_out > 2)
		close(data->fd.cmd_out);
	free(data->hd.data);
	data->hd.data = NULL;
}

void	set_hd_io(t_data *data)
{
	dup2(data->fd.cmd_out, STDOUT_FILENO);
	if (data->fd.cmd_in > 2)
		close(data->fd.cmd_in);
	if (data->fd.cmd_out > 2)
		close(data->fd.cmd_out);
	if (data->fd.cmd_next_in > 2)
		close(data->fd.cmd_next_in);
	data->exe_flag.front_pipe = 0;
	data->exe_flag.file_out = 0;
}

void	heredoc(t_data *data, t_ltkn *temp)
{
	while (1)
	{
		data->hd.i = 0;
		data->readhd = readline(">");
		if (ft_strncmp(data->readhd, temp->infile,
				ft_strlen(temp->infile) + 1) == 0)
			break ;
		dshd(data);
		data->hd.data = ft_mini_strjoin(data->hd.data, data->readhd, 1, data);
		if (data->readhd)
			free(data->readhd);
		data->readhd = NULL;
		data->hd.data = ft_mini_strjoin(data->hd.data, "\n", 1, data);
	}
	data->fd.cmd_in = data->fd.cmd_next_in;
	set_hd_io(data);
	if (data->hd.data)
		ft_putstr_fd(data->hd.data, STDOUT_FILENO);
	if (data->fd.cmd_out > 2)
		close(data->fd.cmd_out);
	if (data->readhd)
		ft_freenull(&data->readhd);
	mini_reset(data);
	exit_free(data, 1);
	exit (0);
}

void	heredoc_set(t_data *data, t_ltkn *temp)
{
	if (data->hdpid > 0)
		waitpid(data->hdpid, NULL, 0);
	data->hd.i = 0;
	if (data->fd.cmd_in > 2)
		close(data->fd.cmd_in);
	ft_pipe(data);
	data->hdprocess = 1;
	data->pid.pid[data->pid.index] = fork();
	if (data->pid.pid[data->pid.index] == 0)
		heredoc(data, temp);
	else
	{
		if (data->fd.cmd_in > 2)
			close(data->fd.cmd_in);
		if (data->fd.cmd_out > 2)
			close(data->fd.cmd_out);
		data->fd.cmd_in = data->fd.cmd_next_in;
		data->hdpid = data->pid.pid[data->pid.index];
	}
	data->pid.index++;
	data->hdprocess = 0;
}
