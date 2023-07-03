/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:22 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/03 17:13:01 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	*ft_init_data(char **envp)
{
	static t_data	*data;

	if (!data)
	{
		data = ft_calloc(1, sizeof(t_data));
		if (!data)
			exit (1);
		build_env(data, envp);
		data->child = getpid();
	}
	return (data);
}

void	mini_exit(t_data *data, t_ltkn *temp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_printf("exit\n");
	while (temp && temp->arg[j])
		j++;
	if (j > 2)
	{
		ft_putstr_fd("Minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		return ;
	}
	if (j == 2)
	{
		while (ft_isdigit(temp->arg[1][i]) == 1)
			i++;
		if (i == (int)ft_strlen(temp->arg[1]))
		{
			j = ft_atoi(temp->arg[1]);
			free_list_ltkn(data->ltkn);
			free (data->read);
			free (data->line);
			ft_freeall(data->envp);
			free (data);
			exit(j);
		}
		else 
		{
			ft_putstr_fd("Minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(temp->arg[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			free_list_ltkn(data->ltkn);
			free (data->read);
			free (data->line);
			ft_freeall(data->envp);
			free (data);
			exit(255);
		}
	}
	else
		if(temp)
		{	
			free_list_ltkn(data->ltkn);
			free (data->read);
			free (data->line);
			ft_freeall(data->envp);
			free (data);
		}
		exit(0);
}

int	parse(t_data *data)
{
	if (ft_strlen(data->read) == 0)
		return (1);
	add_history(data->read);
	if (whitespace(data) == 0)
		return (1);
	if (fuckin_quotes(data) == -1)
		return (1);
	prep_line(data);
	if (ft_strlen(data->line) == 0)
		return (1);
	ft_printf("%s\n", data->line);
	make_list_ltkn(data);
	if(!data->ltkn || data->temp_in_mod == -1)
		return (1);
	return (0);
}

void	close_fd(t_data *data)
{
	if(data->fd.cmd_in > 2)
		close(data->fd.cmd_in);
	if(data->fd.cmd_next_in > 2)
		close(data->fd.cmd_next_in);
	if(data->fd.cmd_out > 2)
		close(data->fd.cmd_out);
}

void	mini_reset(t_data *data)
{
	if(data->ltkn)
		free_list_ltkn(data->ltkn);
	data->ltkn = NULL;
	if(data->line)
		free(data->line);
	if(data->read)
		free (data->read);
	// mini_free(data);
	ft_bzero(&data->exe_flag, sizeof(data->exe_flag));
	close_fd(data);
	ft_bzero(&data->fd, sizeof(data->fd));
	ft_bzero(&data->hd, sizeof(data->hd));
	data->temp_infile = NULL;
	data->temp_outfile =  NULL;
	data->temp_in_mod = 0;
	data->temp_out_mod = 0;
	data->read = NULL;
	data->line = NULL;
	data->child_count = getpid();
}

void	main_core(char **envp)
{
	t_data				*data;

	data = ft_init_data(envp);
	signal(SIGINT, sig_handler);
	// signal(SIGQUIT, sig_handler);
	// signal(SIGQUIT, SIG_IGN);
	signal(SIGCHLD, sig_handler);
	while (1)
	{
		while (1)
		{
			data->read = readline("Minishell>");
			ft_printf("data.read %s\n", data->read);
			if(!data->read)
				mini_exit(data, data->ltkn);
			data->rdflag = 1;
			ft_printf("---------------------------------------\n");
			ft_printf("*****************DEBUG*****************\n");
			if (parse(data))
			{
				mini_reset(data);
				break ;
			}
			print_list(data);
			ft_printf("**-^-^-^-^-^-^-^-DEBUG-^-^-^-^-^-^-^-**\n");
			ft_printf("---------------------------------------\n");
			mini_execute(data);
			mini_reset(data);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	if (argc > 1)
		return (0);
	main_core(envp);
}
//TODO reconvertir les caratere qui on ete changer durant le parsing
