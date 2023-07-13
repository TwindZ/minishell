/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_ltkn_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:25:23 by emman             #+#    #+#             */
/*   Updated: 2023/07/12 22:18:01 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_meta(t_data *data, char **arg)
{
	if (!ft_strncmp(arg[data->i], "<<\0", 3)
		|| !ft_strncmp(arg[data->i], "<\0", 2)
		|| !ft_strncmp(arg[data->i], ">>\0", 3)
		|| !ft_strncmp(arg[data->i], ">\0", 2))
		return (1);
	return (0);
}

void	build_cmd_param(t_data *data, char **arg, t_ltkn *temp)
{
	if (strncmp(arg[data->i], "|\0", 2) == 0 && temp)
	{
		temp->front_pipe = 1;
		data->j = 0;
		return ;
	}
	else if (is_meta(data, arg))
		set_meta(data, arg);
	else if (temp)
		temp->arg[data->j++] = arg[data->i];
}

void	print_list(t_data *data)
{
	t_ltkn	*temp;
	int		i;

	temp = data->ltkn;
	while (temp != NULL)
	{
		i = 0;
		ft_printf("\npath : %s\n", temp->path);
		ft_printf("argv : ");
		while (temp->arg[i])
			ft_printf("%s, ", temp->arg[i++]);
		ft_printf("\n");
		ft_printf("infile : %s\n", temp->infile);
		ft_printf("infile mod : %d\n", temp->in_mod);
		ft_printf("outfile : %s\n", temp->outfile);
		ft_printf("outfile mod : %d\n", temp->out_mod);
		ft_printf("frontpipe : %i\n\n", temp->front_pipe);
		temp = temp->next;
	}
}
