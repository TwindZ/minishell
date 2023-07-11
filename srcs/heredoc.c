/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:51:03 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/11 13:08:41 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	hd_out(t_data *data)
{
	data->fd.cmd_in = data->fd.cmd_next_in;
	ft_putstr_fd(data->hd.data, data->fd.cmd_out);
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
	// dup2(STDIN_FILENO, 0);
	// dup2(STDOUT_FILENO, 1);
	data->exe_flag.front_pipe = 0;
	data->exe_flag.file_out = 0;
}

void	heredoc(t_data *data, char *delimiter)
{
	data->readhd = NULL;
	while (1)
	{
		data->hd.i = 0;
		data->readhd = readline(">");
		if (ft_strncmp(data->readhd, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		while (data->readhd[data->hd.i])
		{
			dollar_sign_hd(data);
			data->hd.i++;
		}
		data->hd.data = ft_strjoin(data->hd.data, data->readhd, 1);
		data->dshd.flag = 0;
		freenull(data->readhd);
		// if (data->linetemp != NULL)
		// 	freenull(data->linetemp);
		data->hd.data = ft_strjoin(data->hd.data, "\n", 1);
	}
	data->fd.cmd_in = data->fd.cmd_next_in;
	set_hd_io(data);
	ft_putstr_fd(data->hd.data, STDOUT_FILENO);
	close(data->fd.cmd_out);
	exit(0);
}

void	heredoc_set(t_data *data, char *delimiter)
{
	data->hd.i = 0;
	if (data->fd.cmd_in > 2)
		close(data->fd.cmd_in);
	ft_pipe(data);
	data->hdprocess = 1;
	data->pid.pid[data->pid.index] = fork();
	if (data->pid.pid[data->pid.index] == 0)
		heredoc(data, delimiter);
	else
	{
		if (data->fd.cmd_in > 2)
			close(data->fd.cmd_in);
		if (data->fd.cmd_out > 2)
			close(data->fd.cmd_out);
		data->fd.cmd_in = data->fd.cmd_next_in;
	}
	data->pid.index++;
	data->hdprocess = 0;
}
