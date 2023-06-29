/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_meta.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:33:30 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/29 13:17:49 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_out_trunk(t_data *data, char **arg)
{
	free(arg[data->i++]);
	if (arg[data->i] && is_meta(data, arg) == 0 && ft_strncmp(arg[data->i], "|\0", 2))
	{
		open_outfile(data, arg[data->i], 0); //TODO si fichier qui suis est un token besoin d'erreur
		data->temp_out_mod = 1;
		if (data->temp_outfile)
			free(data->temp_outfile);
		data->temp_outfile = arg[data->i];
	}
	else
	{
		if (data->temp_outfile)
			free(data->temp_outfile);
		free(arg[data->i]);
		ft_putstr_fd("Minishell: syntax error near unexpected token\n", 2);
		return ;
	}
}

void	set_out_apend(t_data *data, char **arg)
{
	free(arg[data->i++]);
	if (arg[data->i] && is_meta(data, arg) == 0 && ft_strncmp(arg[data->i], "|\0", 2))
	{
		open_outfile(data, arg[data->i], 0); //TODO si fichier qui suis est un token besoin d'erreur
		data->temp_out_mod = 2;
		if (data->temp_outfile)
			free(data->temp_outfile);
		data->temp_outfile = arg[data->i];
	}
	else
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token\n", 2);
		return ;
	}
}

void	set_infile(t_data *data, char **arg)
{
	int	fd;
	
	fd = 0;
	free(arg[data->i++]);
	if(data->temp_in_mod == -1)
	{
		free (arg[data->i++]);
		return;
	}
	if (arg[data->i] && is_meta(data, arg) == 0 && ft_strncmp(arg[data->i], "|\0", 2))
	{
		fd = open(arg[data->i], O_RDONLY);
		if(fd == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(arg[data->i], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			data->temp_in_mod = -1;
			free (arg[data->i++]);
		}
		else
		{
			data->temp_in_mod = 1;
			data->temp_infile = arg[data->i];
		}
		if(fd > 2)
			close (fd);
	}
	else
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token\n", 2);
		return ;
	}
}

void	set_heredoc(t_data *data, char **arg)
{
	free(arg[data->i++]);
	if (arg[data->i] && is_meta(data, arg) == 0 && ft_strncmp(arg[data->i], "|\0", 2))
	{
		data->temp_in_mod = 2;
		data->temp_infile = arg[data->i];
	}
	else
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token\n", 2);
		return ;
	}
}

void	set_meta(t_data *data, char **arg)
{
	if (ft_strncmp(arg[data->i], ">\0", 2) == 0)
		set_out_trunk(data, arg);
	else if (ft_strncmp(arg[data->i], ">>\0", 3) == 0)
		set_out_apend(data, arg);
	else if (ft_strncmp(arg[data->i], "<\0", 2) == 0) //TODO si fichier qui suis est un token besoin d'erreur
		set_infile(data, arg);
	else if (ft_strncmp(arg[data->i], "<<\0", 3) == 0) //TODO si fichier qui suis est un token besoin d'erreur
		set_heredoc(data, arg);
}
