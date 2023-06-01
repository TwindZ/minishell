/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/01 13:24:05 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char file_test[] = "outfile.txt";
char *argv1[] = {"env", NULL};
char path1[] = "/usr/bin/env";
char *argv2[] = {"grep", "PATH", NULL};
char path2[] = "/usr/bin/grep";
char *argv3[] = {"cat", "-e", NULL};
char path3[] = "/bin/cat";
char *argv4[] = {"wc", NULL};
char path4[] = "/usr/bin/wc";
char *argv5[] = {"echo", "allo$USER toiallo", NULL};
char path5[] = "/bin/echo";	
char *argv6[] = {"ls", NULL};
char path6[] = "/bin/ls";
	
void open_outfile(t_data *data)
{

	if(data->exe_flag.file_out_w == 1)
	{
		data->fd.cmd_out = open(file_test, O_WRONLY | O_TRUNC | O_CREAT, 00644);
	}
	else if(data->exe_flag.file_out_a == 1)
		data->fd.cmd_out = open(file_test, O_WRONLY | O_APPEND | O_CREAT, 00644);
}

void set_io(t_data *data)
{
	if (/*data->exe_flag.back_pipe || */data->exe_flag.file_in)
		dup2(data->fd.cmd_in, STDIN_FILENO);		
	else
		close(data->fd.cmd_in);
	if (/*data->exe_flag.front_pipe || */data->exe_flag.file_out_w)
		dup2(data->fd.cmd_out, STDOUT_FILENO);
	else
		close(data->fd.cmd_out);
}

void executer(t_data *data, char *path, char **argv)
{
	int id;
	
	id = fork();
	if (id == 0)
	{		
		
		ft_printf("fd read child :%d\n", data->fd.cmd_out);
		set_io(data);
		execve(path, argv, data->envp);
		exit(EXIT_FAILURE);
	}
	else
	{	
		close(data->fd.cmd_in);
		close(data->fd.cmd_out);
		// data->fd.cmd_in = data->fd.cmd_next_in;
		// data->exe_flag.back_pipe = 1; //peut etre besoin de set ailleur a cause de outfile ?
	}
	wait (NULL);
}

// static void ft_pipe(t_data *data)
// {
// 	// besoin de fonction pour front_pipe et de faire fonctionner avec t_data 
// 	int fd[2];
	
// 	if(data->exe_flag.front_pipe == 1)
// 	{
// 		pipe(fd);
// 		data->fd.cmd_next_in = fd[0];
// 		data->fd.cmd_out = fd[1];
// 	}	
// }

void mini_execute(t_data *data)
{
	// data->exe_flag.front_pipe = 0;
	data->exe_flag.file_out_w = 1;
	open_outfile(data);
	// if(data->exe_flag.front_pipe)
	// 	ft_pipe(data);
	executer(data, path1, argv1);
	// if(data->exe_flag.front_pipe)
	// 	ft_pipe(data);
	// executer(data, path2, argv2);
	// if(data->exe_flag.front_pipe)
	// 	ft_pipe(data);
	// executer(data, path3, argv3);
	// data->exe_flag.front_pipe = 0;
	// if(data->exe_flag.front_pipe)
	// 	ft_pipe(data);
	// executer(data, path4, argv4);
}