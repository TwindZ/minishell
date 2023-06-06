/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/06 10:07:12 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char infile[] = "infile.txt";
char outfile[] = "outfile.txt";
char *argv_env[] = {"env", NULL};
char path_env[] = "/usr/bin/env";
char *argv_grep[] = {"grep", "PATH", NULL};
char path_grep[] = "/usr/bin/grep";
char *argv_cat[] = {"cat", "-e", NULL};
char path_cat[] = "/bin/cat";
char *argv_wc[] = {"wc", NULL};
char path_wc[] = "/usr/bin/wc";
char *argv_echo[] = {"echo", "allo$USER toiallo", NULL};
char path_echo[] = "/bin/echo";	
char *argv_ls[] = {"ls", "-l", "-a", NULL};
char path_ls[] = "/bin/ls";

void open_infile(t_data *data)
{
	if(data->exe_flag.file_in)
		data->fd.cmd_in = open(infile, O_RDONLY);
	if(data->fd.cmd_in == -1)
		ft_putstr_fd("minshell: {COMMAND}: No such file of directory", 2);
}

void open_outfile(t_data *data)
{
	if(data->exe_flag.file_out_w)
	{
		data->fd.cmd_out = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 00644);
	}
	else if(data->exe_flag.file_out_a)
		data->fd.cmd_out = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 00644);
	if (data->fd.cmd_out == -1)
		ft_putstr_fd("minishell : file can't be create", 2);
}

void set_io(t_data *data)
{
	if (data->exe_flag.back_pipe || data->exe_flag.file_in)
	{
		dup2(data->fd.cmd_in, STDIN_FILENO);
		// ft_printf("fd read child 1:%d\n", data->fd.cmd_in);
	}
	else if (data->fd.cmd_in != 0)
		close(data->fd.cmd_in);
	if (data->exe_flag.front_pipe || data->exe_flag.file_out_w)
		dup2(data->fd.cmd_out, STDOUT_FILENO);
	else if (data->exe_flag.back_pipe)
		close(data->fd.cmd_out);
}

void executer(t_data *data, char *path, char **argv)
{
	int id;
	
	id = fork();
	if (id == 0)
	{		
		
		// ft_printf("fd read child 2:%d\n", data->fd.cmd_in);
		// ft_printf("fd read child 2:%d\n", data->exe_flag.file_in);
		set_io(data);
		// ft_printf("fd read child 3:%d\n", data->fd.cmd_in);
		// ft_printf("fd read child 4:%d\n", execve(path, argv, data->envp));
		execve(path, argv, data->envp);
		exit(EXIT_FAILURE);
	}
	else
	{	
		close(data->fd.cmd_in);
		close(data->fd.cmd_out);
		data->fd.cmd_in = data->fd.cmd_next_in;
	}
	wait (NULL);
}

void ft_pipe(t_data *data)
{
	//TODO besoin de fonction pour front_pipe et de faire fonctionner avec t_data 
	int fd[2];

	pipe(fd);
	data->fd.cmd_next_in = fd[0];
	data->fd.cmd_out = fd[1];
	data->exe_flag.back_pipe = 1;  //TODO peut etre besoin de set ailleur a cause de outfile ?
}

void	heredoc(t_data *data)
{
	char 	*read;
	read = NULL;
	data->heredoc.end = ft_strjoin(NULL, "!", 0);
	while(1)
	{
		read = readline(">");
		if(!(ft_strncmp(read, data->heredoc.end, ft_strlen(data->heredoc.end))))
			break;
		data->heredoc.data = ft_strjoin(data->heredoc.data, read, 1);
		free(read);
		data->heredoc.data = ft_strjoin(data->heredoc.data, "\n", 1);
	}
	//analiser les $ "" ''
	ft_pipe(data);
	data->fd.cmd_in = data->fd.cmd_next_in;
	ft_putstr_fd(data->heredoc.data, data->fd.cmd_out);
	close(data->fd.cmd_out);
	data->exe_flag.back_pipe = 1;
	free(read);
}

void mini_execute(t_data *data)
{
	
	heredoc(data);
	// data->exe_flag.front_pipe = 1;
	// ft_pipe(data);
	executer(data, path_cat, argv_cat);
	// data->exe_flag.file_in = 0;
	// if(data->exe_flag.front_pipe)
	// data->exe_flag.file_in = 1;
	// open_infile(data);
	// ft_pipe(data);
	// data->exe_flag.front_pipe = 0;
	// executer(data, path_wc, argv_wc);
	// data->exe_flag.file_out_w = 1;
	// open_outfile(data);
	// executer(data, path_grep, argv_grep);
	// executer(data, path_wc, argv_wc);
	// data->exe_flag.file_out_w = 0;
	// if(data->exe_flag.front_pipe)
	// if(data->exe_flag.front_pipe)
	// ft_pipe(data);
	// if(data->exe_flag.front_pipe)
	// 	ft_pipe(data);
	// executer(data, path4, argv4);
}
