/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_meta.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:33:30 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/13 15:20:15 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_out(t_data *data, char **arg, int mod)
{
	free(arg[data->i]);
	data->i++;
	if (arg[data->i] && is_meta(data, arg) == 0
		&& ft_strncmp(arg[data->i], "|\0", 2))
	{
		open_outfile(data, arg[data->i], 0); 
		data->temp_out_mod = mod;
		if (data->temp_outfile)
			free(data->temp_outfile);
		data->temp_outfile = arg[data->i];
	}
	else
	{
		if (data->temp_outfile)
			free(data->temp_outfile);
		free(arg[data->i]);
		data->syntax = -1;
		ft_putstr_fd("Minishell: syntax error near unexpected token\n", 2);
		return ;
	}
}

void	check_infile(t_data *data, char **arg)
{
	int	fd;

	fd = 0;
	fd = open(arg[data->i], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(arg[data->i], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->temp_in_mod = -1;
		free(arg[data->i]);
		data->i++;
	}
	else
	{
		data->temp_in_mod = 1;
		if(data->temp_infile)
			free(data->temp_infile);
		data->temp_infile = arg[data->i];
	}
	if (fd > 2)
		close (fd);
}

void	set_infile(t_data *data, char **arg)
{
	free(arg[data->i]);
	data->i++;
	if (data->temp_in_mod == -1)
	{
		free(arg[data->i]);
		data->i++;
		return ;
	}
	if (arg[data->i] && is_meta(data, arg) == 0 
		&& ft_strncmp(arg[data->i], "|\0", 2))
		check_infile(data, arg);
	else
	{
		data->syntax = -1;
		ft_putstr_fd("Minishell: syntax error near unexpected token\n", 2);
		return ;
	}
}

void	set_heredoc(t_data *data, char **arg)
{
	free(arg[data->i]);
	arg[data->i] = NULL;
	data->i++;
	if (arg[data->i] && is_meta(data, arg) == 0
		&& ft_strncmp(arg[data->i], "|\0", 2) && ft_strncmp(arg[data->i], "\n", 2))
	{
		data->temp_in_mod = 2;
		data->temp_infile = arg[data->i];
	}
	else
	{
		data->syntax = -1;
		ft_putstr_fd("Minishell: syntax error near unexpected token\n", 2);
		return ;
	}
	data->pid.count++;
}

void	set_meta(t_data *data, char **arg)
{
	if (ft_strncmp(arg[data->i], ">\0", 2) == 0)
		set_out(data, arg, 1);
	else if (ft_strncmp(arg[data->i], ">>\0", 3) == 0)
		set_out(data, arg, 2);
	else if (ft_strncmp(arg[data->i], "<\0", 2) == 0)
		set_infile(data, arg);
	else if (ft_strncmp(arg[data->i], "<<", 3) == 0)
		set_heredoc(data, arg);
}
