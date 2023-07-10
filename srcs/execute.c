/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/10 16:29:11 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char infile[] = "outfile.txt";
// char outfile[] = "outfile.txt";
// char *argv_env[] = {"env", NULL};
// char path_env[] = "/usr/bin/env";
// char *argv_grep[] = {"grep", "PATH", NULL};
// char path_grep[] = "/usr/bin/grep";
// char *argv_cat[] = {"cat", "-e", NULL};
// char path_cat[] = "/bin/cat";
// char *argv_wc[] = {"wc", NULL};
// char path_wc[] = "/usr/bin/wc";
// char *argv_echo[] = {"echo", "allo$USER toiallo", NULL};
// char path_echo[] = "/bin/echo";	
// char *argv_ls[] = {"", "-la", NULL};
// char path_ls[] = "/bin/ls";

void	builtin(t_data *data, t_ltkn *temp)
{
	if (ft_strncmp(temp->arg[0], "echo\0", 5) == 0)
		mini_echo(data->fd.cmd_out, temp, data);
	else if (ft_strncmp(temp->arg[0], "pwd\0", 4) == 0)
		mini_pwd(data->fd.cmd_out, data);
	else if (ft_strncmp(temp->arg[0], "env\0", 4) == 0)
		mini_env(data);
	else if (ft_strncmp(temp->arg[0], "cd\0", 3) == 0)
		mini_cd(data, temp);
	else if (ft_strncmp(temp->arg[0], "export\0", 7) == 0)
		mini_export(data->fd.cmd_out, data, temp);
	else if (ft_strncmp(temp->arg[0], "unset\0", 6) == 0)
		mini_unset(data, temp);
	else if (ft_strncmp(temp->arg[0], "exit\0", 5) == 0)
		mini_exit(data, temp);
	data->fd.cmd_in = data->fd.cmd_next_in;
	if (data->fd.cmd_out > 2)
		close(data->fd.cmd_out);
}
	// else if (ft_strncmp(temp->arg[0], "exit\0", 5) == 0)
	// 	mini_exit(data); //TODO si on a le gout ! heurk et &&

void	set_io(t_data *data)
{
	if (data->exe_flag.back_pipe || data->exe_flag.file_in)
		dup2(data->fd.cmd_in, STDIN_FILENO);
	if (data->exe_flag.front_pipe || data->exe_flag.file_out)
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

void	executer(t_data *data, char *path, char **argv)
{	
	data->exeprocess = 1;
	data->pid.pid[data->pid.index] = fork();
	if (data->pid.pid[data->pid.index] == 0)
	{
		
		signal(SIGQUIT, SIG_DFL);
		set_io(data);
		if(execve(path, argv, data->envp) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		if (data->fd.cmd_in > 2)
			close(data->fd.cmd_in);
		if (data->fd.cmd_out > 2)
			close(data->fd.cmd_out);
		data->fd.cmd_in = data->fd.cmd_next_in;
	}
	// ft_printf("child %d\n", data->pid.pid[data->pid.index]);
	data->pid.index++;
	// data->exeprocess = 0;
}

//TODO si fini par un meta doit detecter un \n
void	mini_execute(t_data *data)
{
	int	status;

	status = 0;
	// ft_printf("child %d\n", data->pid.count);
	t_ltkn	*temp;
	
	
	if(data->pid.count > 0)
		data->pid.pid = ft_safe_calloc(data->pid.count, sizeof(int), data);
	temp = data->ltkn;
	
	while (temp != NULL)
	{
		// ft_printf("child %s\n", temp->path);
		data->exe_flag.front_pipe = temp->front_pipe;
		if (temp->in_mod == 1)
			open_infile(data, temp->infile);//TODO si un de pas bon ne dois pas marcher
		if (temp->in_mod == 2)
			heredoc_set(data, temp->infile);
		if (temp->out_mod > 0)
			open_outfile(data, temp->outfile, temp->out_mod);
		if (temp->front_pipe)
			ft_pipe(data);
		if (!temp->path || ft_strncmp(temp->path, "*directory", 10) == 0)
			break ;
		else if (strncmp(temp->path, "*builtin", 9) == 0)
			builtin(data, temp);
		else if (temp->path)
			executer(data, temp->path, temp->arg);
		temp = temp->next;
	}
	data->pid.index = 0;
	while(data->pid.count > 0)
	{
		// ft_printf("child count mini execute %d\n", data->pid.count);
		// ft_printf("child count mini execute %d\n", data->pid.pid[data->pid.index]);
		waitpid(data->pid.pid[data->pid.index], &status, 0);
		data->pid.index++;
		data->pid.count--;
		// ft_printf("status : %i ", WIFEXITED(status));
		// ft_printf("status : %i ", WEXITSTATUS(status));
		// ft_printf("status : %i ", WIFSIGNALED(status));
		// ft_printf("status : %i\n", WTERMSIG(status));
		if(WIFEXITED(status))
			data->prevout = WEXITSTATUS(status);
		else if(WIFSIGNALED(status))
		{
			if(WTERMSIG(status) == 2)
				data->prevout = 130;
			else if(WTERMSIG(status) == 3)
			{
				ft_putstr_fd("Quit : 3\n", STDOUT_FILENO);
				data->prevout = 131;
			}
			else
				data->prevout = WTERMSIG(status);
		}
		
		
	}
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
