/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_ltkn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:23:39 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/18 13:37:05 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_count_arg(char **arg, int i)
{
	int	j;

	j = 0;
	while ((ft_strncmp(arg[i], "|\0", 2)) && arg[i++])
		j++;
	return (j);
}

void	set_redirect(t_data *data, char **arg, t_ltkn *temp)
{
	if (temp && data->j > 0)
	{
		temp->in_mod = data->temp_in_mod;
		temp->out_mod = data->temp_out_mod;
		if(temp->infile)
			free(temp->infile);
		if(temp->outfile)
			free(temp->outfile);
		temp->outfile = NULL;
		temp->infile = NULL;
		temp->infile = ft_mini_strdup(data->temp_infile, data);
		temp->outfile = ft_mini_strdup(data->temp_outfile, data);
		free(data->temp_outfile);
		data->temp_outfile = NULL;
		free(data->temp_infile);
		data->temp_infile = NULL;
	}
	else if (temp && strncmp(arg[data->i], "|\0", 2) == 0)
	{
		data->temp_in_mod = 0;
		data->temp_out_mod = 0;
		data->temp_infile = NULL;
		data->temp_outfile = NULL;
		free(arg[data->i]);
	}
}

void	create_list(t_data *data, t_ltkn *temp, char **arg)
{
	while (arg[data->i])
	{
		if (data->j == 0 && is_meta(data, arg) == 0
			&& ft_strncmp(arg[data->i], "|\0", 2))
			temp = new_node(data, arg, temp);
		else
			build_cmd_param(data, arg, temp);
		if (arg[data->i] == NULL || data->temp_in_mod == -1
			|| data->syntax == -1)
			break ;
		if (temp)
			set_redirect(data, arg, temp);
		data->i++;
	}
}

void	make_list_ltkn(t_data *data)
{
	char	**arg;
	t_ltkn	*temp;

	temp = NULL;
	data->i = 0;
	data->j = 0;
	arg = NULL;
	arg = ft_split(data->line, 29);
	if (!arg)
		return ;
	create_list(data, temp, arg);
	if (arg)
		free(arg);
	arg = NULL;
}
