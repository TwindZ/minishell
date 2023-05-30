/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/05/30 12:51:47 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *argv1[] = {"env", NULL};
char path1[] = "/usr/bin/env";
char *argv2[] = {"grep", "PATH", NULL};
char path2[] = "/usr/bin/grep";
char *argv3[] = {"cat", "-e", NULL};
char path3[] = "/bin/cat";
char *argv4[] = {"wc", NULL};
char path4[] = "/usr/bin/wc";
char *argv5[] = {"echo", "$", NULL};
char path5[] = "/bin/echo";	
char *argv6[] = {"ls", "/usr/bin", NULL};
char path6[] = "/bin/ls";
	
void set_io(t_data *data, int fd[2])
{
	if (data->back_pipe)
		dup2(data->oldfdr, STDIN_FILENO);
	else
		close(data->oldfdr);
	if (data->front_pipe)
		dup2(fd[1], STDOUT_FILENO);
	else
		close(fd[1]);
}

void ft_pipe(t_data *data, char *path, char **argv)
{
	// besoin de fonction pour front_pipe et de faire fonctionner avec t_data 
	int id;
	int fd[2];
	
	if(data->front_pipe == 1)
		pipe(fd);
	id = fork();
	if (id == 0)
	{		
		set_io(data, fd);
		execve(path, argv, data->envp);
		exit(EXIT_FAILURE);
	}
	else
	{	
		data->oldfdr = fd[0];
		data->back_pipe = 1;
		close(fd[1]);
	}
	wait (NULL);
}

void mini_execute(t_data *data)
{
	data->front_pipe = 1;
	ft_pipe(data, path1, argv1);
	ft_pipe(data, path2, argv2);
	ft_pipe(data, path3, argv3);
	data->front_pipe = 0;
	ft_pipe(data, path4, argv4);
	
}