/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:51:03 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/03 17:32:15 by emlamoth         ###   ########.fr       */
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
	data->hd.data = NULL;
	data->exe_flag.back_pipe = 1;
}

int	heredoc(t_data *data, char *delimiter)
{
	
	data->hdprocess = 1;
	data->hd.i = 0;
	data->readhd = NULL;
	if (data->fd.cmd_in > 2)
		close(data->fd.cmd_in);
	data->child = getpid();
	data->child = fork();
	if(data->child == 0)
	{
		
		while (data->hdprocess)
		{
			data->readhd = readline(">");
			if(!data->readhd)
			{
				ft_printf("HEREDOC ici %s", data->readhd);
				return (1);
			}
			if (ft_strncmp(data->readhd, delimiter, ft_strlen(delimiter)) == 0)
				break ;
			data->hd.data = ft_strjoin(data->hd.data, data->readhd, 1);
			while (data->hd.data[data->hd.i])
			{
				dollar_sign_hd(data);
				data->hd.i++;
			}
			// free(data->readhd);
			data->readhd = NULL;
			data->hd.data = ft_strjoin(data->hd.data, "\n", 1);
		}
		if (data->hd.data)
			hd_out(data);
		free(data->readhd);
		data->readhd = NULL;
		data->hdprocess = 0;
		exit(0);
	}
	else
		wait(NULL);
		printf("dekc");
	return (0);
}
