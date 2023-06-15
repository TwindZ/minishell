/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/15 17:12:28 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char infile[] = "outfile.txt";
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
char *argv_ls[] = {"", "-la", NULL};
char path_ls[] = "/bin/ls";

void open_infile(t_data *data, char *file)
{
	if(data->exe_flag.back_pipe)
	{
		data->exe_flag.back_pipe = 0;
		if(data->fd.cmd_in > 2)
			close(data->fd.cmd_in);
	}
	data->fd.cmd_in = open(file , O_RDONLY);
	data->exe_flag.file_in = 1;
	if(data->fd.cmd_in == -1)
		ft_putstr_fd("minshell: {COMMAND}: No such file of directory", 2);
} // si fichier existe pas

void open_outfile(t_data *data, char *file, int mod)
{
	if(mod == 1)
		data->fd.cmd_out = open(file, O_WRONLY | O_TRUNC | O_CREAT, 00644);
	else if(mod == 2)
		data->fd.cmd_out = open(file, O_WRONLY | O_APPEND | O_CREAT, 00644);
	if (data->fd.cmd_out == -1)
		ft_putstr_fd("minishell : file can't be create", 2);
	data->exe_flag.file_out = 1;
}

void set_io(t_data *data)
{
	if (data->exe_flag.back_pipe || data->exe_flag.file_in)
		dup2(data->fd.cmd_in, STDIN_FILENO);
	else if (data->fd.cmd_in != 0)
		close(data->fd.cmd_in);
	if (data->exe_flag.front_pipe || data->exe_flag.file_out)
		dup2(data->fd.cmd_out, STDOUT_FILENO);
	else if (data->exe_flag.back_pipe)
		close(data->fd.cmd_out);
	data->exe_flag.front_pipe = 0;
	data->exe_flag.file_out = 0;
}

void executer(t_data *data, char *path, char **argv)
{
	(void)	path;
	(void)	argv;
	int id;
	
	id = fork();
	if (id == 0)
	{		
		set_io(data);
		execve(path, argv, data->envp);
		exit(EXIT_FAILURE);
	}
	else
	{	
		if(data->exe_flag.front_pipe || data->exe_flag.back_pipe)
		{
			if(data->exe_flag.back_pipe && data->fd.cmd_in > 2)
			close(data->fd.cmd_in);
			close(data->fd.cmd_out);
		}
		data->fd.cmd_in = data->fd.cmd_next_in;
	}
	wait (NULL);
}

void ft_pipe(t_data *data)
{
	//TODO besoin de fonction pour front_pipe et de faire fonctionner avec t_data 
	int fd[2];

	if(data->exe_flag.file_out == 0)
	{
		pipe(fd);
		data->fd.cmd_next_in = fd[0];
		data->fd.cmd_out = fd[1];
		data->exe_flag.back_pipe = 1;
		
	} //TODO peut etre besoin de set ailleur a cause de outfile ?
}

void	heredoc(t_data *data)
{
	data->hd.i = 0;
	data->readhd = NULL;
	while(1)
	{
		data->readhd = readline(">");
		if(!(ft_strncmp(data->readhd, data->hd.end, ft_strlen(data->hd.end))))
			break;
		data->hd.data = ft_strjoin(data->hd.data, data->readhd, 1);
		while (data->hd.data[data->hd.i])
		{
			dollar_sign_hd(data);
			data->hd.i++;
		}
		free(data->readhd);
		data->hd.data = ft_strjoin(data->hd.data, "\n", 1);
	}
	if(data->hd.data)
	{
		ft_pipe(data);
		data->fd.cmd_in = data->fd.cmd_next_in;
		ft_putstr_fd(data->hd.data, data->fd.cmd_out);
		close(data->fd.cmd_out);
		data->exe_flag.back_pipe = 1;
	}
	free(data->readhd);	
}

void mini_execute(t_data *data)
{
	// TODO doit créé tout les fichier de redirection meme s'il en a plusieur
	// TODO ligne de commande peut commencer par une redirection
	
	t_ltkn *temp;

	temp = data->ltkn;
	while(temp != NULL)
	{
		data->exe_flag.front_pipe = temp->front_pipe;
		if(temp->front_pipe)
			ft_pipe(data);
		if(temp->in_mod == 1)
			open_infile(data, temp->infile);
		if(temp->in_mod == 2)
			heredoc(data);
		if(temp->out_mod != 0)
			open_outfile(data, temp->outfile, temp->out_mod);
		executer(data, temp->path, temp->arg);
		temp = temp->next;
	}
	// data->exe_flag.back_pipe = 0;
	// dup2(0, STDIN_FILENO);
	// dup2(1, STDOUT_FILENO);
	// heredoc(data);
	// ft_pipe(data);
	// data->file = "outfile3.txt";
	// data->exe_flag.file_in = 0;
	// data->exe_flag.file_in = 1;
	// open_infile(data);
	// data->exe_flag.front_pipe = 1;
	// ft_pipe(data);
	// executer(data, path_env, argv_env);
	// ft_pipe(data);
	// executer(data, path_grep, argv_grep);
	// data->exe_flag.front_pipe = 0;
	// executer(data, path_cat, argv_cat);
	// if(data->exe_flag.front_pipe)
	
	// data->exe_flag.file_out_w = 1;
	// open_outfile(data);
	// executer(data, path_wc, argv_wc);
	// data->exe_flag.file_out_w = 0;
	// if(data->exe_flag.front_pipe)
	// if(data->exe_flag.front_pipe)
	// ft_pipe(data);
	// if(data->exe_flag.front_pipe)
	// executer(data, path4, argv4);
}
