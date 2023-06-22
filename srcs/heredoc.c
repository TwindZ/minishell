/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:51:03 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/22 10:12:30 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	hd_out(t_data *data)
{
	ft_pipe(data);
	data->fd.cmd_in = data->fd.cmd_next_in;
	ft_putstr_fd(data->hd.data, data->fd.cmd_out);
	close(data->fd.cmd_out);
	free(data->hd.data);
	data->exe_flag.back_pipe = 1;
}

void	heredoc(t_data *data, char *delimiter)
{
	data->hd.i = 0;
	data->readhd = NULL;
	if (data->fd.cmd_in > 2)
		close(data->fd.cmd_in);
	while (1)
	{
		data->readhd = readline("heredoc>");
		if (!(ft_strncmp(data->readhd, delimiter, ft_strlen(delimiter))))
			break ;
		data->hd.data = ft_strjoin(data->hd.data, data->readhd, 1);
		while (data->hd.data[data->hd.i])
		{
			dollar_sign_hd(data);
			data->hd.i++;
		}
		free(data->readhd);
		data->hd.data = ft_strjoin(data->hd.data, "\n", 1);
	}
	if (data->hd.data)
		hd_out(data);
	free(data->readhd);
}