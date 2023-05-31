/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/05/31 18:20:36 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char file_test[] = "outfile.txt";
char *argv1[] = {"env", NULL};
char path1[] = "/usr/bin/env";
char *argv2[] = {"grep", "donc", NULL};
char path2[] = "/usr/bin/grep";
char *argv3[] = {"cat", "-e", NULL};
char path3[] = "/bin/cat";
char *argv4[] = {"wc", NULL};
char path4[] = "/usr/bin/wc";
char *argv5[] = {"echo", "allo$USER toiallo", NULL};
char path5[] = "/bin/echo";	
char *argv6[] = {"ls", "fbouchar", NULL};
char path6[] = "/bin/ls";
	
static void file_open(t_data *data)
{
	if(access(file_test, F_OK))
		data->fd.cmd_out = open(file_test, O_CREAT);
	else
		data->fd.cmd_out = open(file_test, O_RDWR);
	data->file_out = 1;
	ft_printf("fd read :%d\n", data->fd.cmd_out);
}

static void set_io(t_data *data)
{
	if (data->back_pipe || data->file_in)
		dup2(data->fd.cmd_in, STDIN_FILENO);		
	else
		close(data->fd.cmd_in);
	if (data->front_pipe || data->file_out)
		{
			dup2(data->fd.cmd_out, STDOUT_FILENO);
		}
	else
		close(data->fd.cmd_out);
}

static void ft_pipe(t_data *data, char *path, char **argv)
{
	// besoin de fonction pour front_pipe et de faire fonctionner avec t_data 
	int id;
	int fd[2];
	
	if(data->front_pipe == 1)
	{
		pipe(fd);
		data->fd.cmd_next_in = fd[0];
		data->fd.cmd_out = fd[1];
	}
	id = fork();
	if (id == 0)
	{		
		set_io(data);
		execve(path, argv, data->envp);
		exit(EXIT_FAILURE);
	}
	else
	{	
		close(data->fd.cmd_in);
		close(data->fd.cmd_out);
		data->fd.cmd_in = data->fd.cmd_next_in;
		data->back_pipe = 1; //peut etre besoin de set ailleur a cause de outfile ?
	}
	wait (NULL);
}

void mini_execute(t_data *data)
{
	data->front_pipe = 0;
	file_open(data);
	ft_pipe(data, path1, argv1);
	// ft_pipe(data, path2, argv2);
	// ft_pipe(data, path3, argv3);
	// data->front_pipe = 0;
	// ft_pipe(data, path4, argv4);
}