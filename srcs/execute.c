/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/16 21:34:15 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		if (execve(path, argv, data->envp) == -1)
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
	data->pid.index++;
}

void	ft_waiting(t_data *data)
{
	int	status;

	status = 0;
	data->pid.index = 0;
	while (data->pid.count > 0)
	{
		waitpid(data->pid.pid[data->pid.index], &status, 0);
		data->pid.index++;
		data->pid.count--;
		if (WIFEXITED(status) && data->exit_out == 0)
			data->prevout = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
				data->prevout = 130;
			else if (WTERMSIG(status) == 3)
			{
				ft_putstr_fd("Quit : 3\n", STDOUT_FILENO);
				data->prevout = 131;
			}
			else
				data->prevout = WTERMSIG(status);
		}
		data->exit_out = 0;
	}
}

void	mini_execute(t_data *data)
{
	t_ltkn	*temp;

	if (data->pid.count > 0)
		data->pid.pid = ft_safe_calloc(data->pid.count, sizeof(int), data);
	temp = data->ltkn;
	while (temp != NULL)
	{
		// meta_replace(temp);
		set_redirection(data, temp);
		if (!temp->path || ft_strncmp(temp->path, "*directory", 10) == 0)
			break ;
		else if (strncmp(temp->path, "*builtin", 9) == 0)
			builtin(data, temp);
		else if (temp->path)
			executer(data, temp->path, temp->arg);
		temp = temp->next;
		data->exe_flag.file_out = 0;
	}
}
