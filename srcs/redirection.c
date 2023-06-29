/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:51:07 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/29 11:32:12 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pipe(t_data *data)
{
	int	fd[2];

	if (data->exe_flag.file_out == 0)
	{
		pipe(fd);
		data->fd.cmd_next_in = fd[0];
		data->fd.cmd_out = fd[1];
		data->exe_flag.back_pipe = 1;
	}
}

void	open_outfile(t_data *data, char *file, int mod)
{
	int	fd;

	fd = 0;
	if (mod == 0)
	{
		fd = open(file, O_WRONLY | O_CREAT, 00644);
		close(fd);
	}
	else
	{
		if (mod == 1)
			data->fd.cmd_out = open(file, O_RDWR | O_TRUNC);
		else if (mod == 2)
			data->fd.cmd_out = open(file, O_RDWR | O_APPEND);
		data->exe_flag.file_out = 1;
	}
	ft_printf("data->fd.cmd_out : %d\n", data->fd.cmd_out);
	if (data->fd.cmd_out == -1 || fd == -1)
		ft_putstr_fd("Minishell : file can't be create", 2);
}

// si fichier existe pas
void	open_infile(t_data *data, char *file)
{
	if (data->exe_flag.back_pipe)
	{
		data->exe_flag.back_pipe = 0;
		if (data->fd.cmd_in > 2)
			close(data->fd.cmd_in);
	}
	data->fd.cmd_in = open(file, O_RDONLY);
	data->exe_flag.file_in = 1;
	if (data->fd.cmd_in == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}
